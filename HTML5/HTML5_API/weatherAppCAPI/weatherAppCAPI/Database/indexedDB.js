

// Öppna en anslutning till IndexDB-databasen
const openDBConnection = () => {
    return new Promise((resolve, reject) => {
      const request = window.indexedDB.open("WeatherDataDB", 1); 
  
      request.onupgradeneeded = event => {
        const db = event.target.result;
        const objectStore = db.createObjectStore("weatherData", { keyPath: "locationId" });
  
        if (!objectStore.indexNames.contains("timestamp")) {
          objectStore.createIndex("timestamp", "timestamp", { unique: false });
        }
        objectStore.createIndex("lat", "lat", { unique: false });
        objectStore.createIndex("lon", "lon", { unique: false });
        objectStore.createIndex("approvedTime", "approvedTime", { unique: false });
        objectStore.createIndex("hourlyData", "hourlyData", { unique: false });
      };
  
      request.onerror = event => {
        reject(event.target.error);
      };
  
      request.onsuccess = event => {
        const db = event.target.result;
        resolve(db);
      };
    });
  };
  
  // Spara den senaste sökningen i IndexDB eller uppdatera befintlig plats
  const saveLatestSearch = async (lat, lon, approvedTime, hourlyData) => {
    try {
      const locationId = `${lat},${lon}`;
      const timestamp = Date.now();
  
      const db = await openDBConnection();
      const transaction = db.transaction(["weatherData"], "readwrite");
      const objectStore = transaction.objectStore("weatherData");
  
      const getRequest = objectStore.get(locationId);
  
      getRequest.onsuccess = event => {
        const existingSearch = event.target.result;
  
        if (existingSearch) {
          existingSearch.approvedTime = approvedTime;
          existingSearch.hourlyData = hourlyData;
          existingSearch.timestamp = timestamp;
  
          const putRequest = objectStore.put(existingSearch);
          putRequest.onsuccess = () => {
            console.log("Search updated in IndexedDB");
          };
          putRequest.onerror = () => {
            console.error("Error updating search");
          };
        } else {
          const putRequest = objectStore.put({ locationId, lat, lon, approvedTime, hourlyData, timestamp });
          putRequest.onsuccess = () => {
            console.log("Latest search saved to IndexedDB");
          };
          putRequest.onerror = () => {
            console.error("Error saving latest search");
          };
        }
      };
  
      getRequest.onerror = event => {
        console.error("Error getting search:", event.target.error);
      };
    } catch (error) {
      console.error("Error saving latest search:", error);
    }
  };
  
  // Hämta den senaste sökningen från IndexDB baserat på tidsstämpel
  const getLatestSearch = async () => {
    try {
      const db = await openDBConnection();
      return new Promise((resolve, reject) => {
        const transaction = db.transaction(["weatherData"], "readonly");
        const objectStore = transaction.objectStore("weatherData");
  
        const index = objectStore.index("timestamp");
  
        const cursorRequest = index.openCursor(null, 'prev');
  
        cursorRequest.onsuccess = event => {
          const cursor = event.target.result;
          if (cursor) {
            resolve(cursor.value);
          } else {
            resolve(null);
          }
        };
  
        cursorRequest.onerror = event => {
          reject(event.target.error);
        };
      });
    } catch (error) {
      console.error("Error getting latest search:", error);
    }
  };
  
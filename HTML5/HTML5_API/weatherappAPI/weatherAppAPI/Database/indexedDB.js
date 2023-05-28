


// Öppna en anslutning till IndexDB-databasen
const openDBConnection = () => {
  return new Promise((resolve, reject) => {
    const request = window.indexedDB.open("searchDB", 2); // Använd en ny version av databasen

    request.onupgradeneeded = event => {
      const db = event.target.result;
      const objectStore = db.createObjectStore("searches", { keyPath: "locationID" });

      // Kolla om indexet redan finns innan du skapar det
      if (!objectStore.indexNames.contains("timeStamp")) {
        objectStore.createIndex("timeStamp", "timeStamp", { unique: false }); // Skapa index för timeStamp
      }
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


// Spara den senaste sökningen i IndexDB
const saveLatestSearch = async (lat, lon, { approvedTime, hourlyData }) => {
  try {
    const locationID = `${lat},${lon}`;
    const timeStamp = new Date().getTime();

    const db = await openDBConnection();
    const transaction = db.transaction(["searches"], "readwrite");
    const objectStore = transaction.objectStore("searches");

    const putRequest = objectStore.put({ locationID, lat, lon, approvedTime, hourlyData, timeStamp });
    putRequest.onsuccess = () => {
      console.log("Latest search saved to IndexedDB");
    };
    putRequest.onerror = () => {
      console.error("Error saving latest search");
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
      const transaction = db.transaction(["searches"], "readonly");
      const objectStore = transaction.objectStore("searches");

      // Skapa en index för timeStamp
      const index = objectStore.index("timeStamp");

      // Öppna en cursor med riktningen satt till "prev" för att hämta senaste sökningen baserat på timeStamp
      const cursorRequest = index.openCursor(null, 'prev');

      cursorRequest.onsuccess = event => {
        const cursor = event.target.result;
        if (cursor) {
          // Om det finns en cursor, hämta värdet
          resolve(cursor.value);
        } else {
          // Om det inte finns någon cursor (dvs. det finns inga objekt i databasen), returnera null
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







const fetchData = async (lat, lon) => {
    try {
      const response = await fetch(`https://opendata-download-metfcst.smhi.se/api/category/pmp3g/version/2/geotype/point/lon/${lon}/lat/${lat}/data.json`,{ 
        method: 'GET',
        cache: 'no-store'  // Lägg till det här
      });
    
      if (!response.ok) {
        throw new Error(`API request failed with status ${response.status}`);
      }

      const data = await response.json();
      return data;
    } catch (error) {
      console.error("Error fetching weather data:", error);
      throw error;
    }
  };
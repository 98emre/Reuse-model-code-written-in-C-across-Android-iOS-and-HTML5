

// Funktion för att hämta väderdata från SMHI API:et
const fetchWeatherData = async (lat, lon) => {
    try {
      const response = await fetch(`https://opendata-download-metfcst.smhi.se/api/category/pmp3g/version/2/geotype/point/lon/${lon}/lat/${lat}/data.json`, {
        method: 'GET',
        cache: 'no-store'  // Lägg till det här
      });
  
      if (!response.ok) {
        throw new Error('Network response was not ok');
      }
  
      return await response.json();
    } catch (error) {
      console.error('There has been a problem with your fetch operation:', error);
    }
  };
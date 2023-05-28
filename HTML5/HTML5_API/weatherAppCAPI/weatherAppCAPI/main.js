
const latInput = document.getElementById("lat");
const lonInput = document.getElementById("lon");
const approvedTimeElement = document.getElementById("approvedTime");
const weatherDataElement = document.getElementById("weatherData").getElementsByTagName("tbody")[0];

const weather = new WeatherData()
const hourlyData = new HourlyData()

const displayWeatherData = async (lat, lon) => {
  try {
    const data = await fetchData(lat,lon)

    approvedTimeElement.innerHTML = `Approved time: ${formatDateTime(data.approvedTime)} <br/> Longitude: ${lon}<br/> Latitude: ${lat}`;

    weatherDataElement.innerHTML = ''; // Clear previous data
    weather.createWeatherObject(formatDateTime(data.approvedTime))

    const weatherViewModel = new WeatherDataViewModel(weather)
    weatherViewModel.updateLocation(lat,lon)

    const hourlyDataToSave = []; // Array to store all time series data

    data.timeSeries.forEach(hourly => {
      let hourlyDataEntry = {}; // Create a new object reference in each iteration

      const time = formatDateTime(hourly.validTime);
      const temperature = hourly.parameters.find(param => param.name === 't').values[0];
      const weatherNumSymbol = hourly.parameters.find(param => param.name === "Wsymb2").values[0];
      const dayOrNight = getTime(time);
      const icon = `<img src="./weather_symbols/${dayOrNight}/${dayOrNight}${weatherNumSymbol}.png" alt="Weather Icon">`;
    
      hourlyData.createHourlyWeatherObject(time, `${temperature}°C`, icon);
      const hourlyViewModel = new HourlyDataViewModel(hourlyData)
    
      weatherViewModel.addHourlyData(hourlyViewModel.getTime(),hourlyViewModel.getTemperature(),hourlyViewModel.getIcon())
      
      hourlyDataEntry = { time: hourlyViewModel.getTime(), temperature: hourlyViewModel.getTemperature(), icon: hourlyViewModel.getIcon() };
      hourlyDataToSave.push(hourlyDataEntry);


      const row = weatherDataElement.insertRow();
      row.insertCell(0).textContent = hourlyViewModel.getTime();
      row.insertCell(1).textContent = hourlyViewModel.getTemperature() ;
      row.insertCell(2).innerHTML = hourlyViewModel.getIcon();

      hourlyViewModel.freeHourlyObject()
    })

    saveLatestSearch(weatherViewModel.getLat(),weatherViewModel.getLon(),weatherViewModel.getApprovedTime(),hourlyDataToSave)
    weatherViewModel.freeWeatherObject()

  } catch (error) {
    console.log("Error " + error);
    alert("Failed to fetch weather data from API.");

  }
};

const form = document.getElementById("inputForm");
form.addEventListener("submit", async (event) => {
  event.preventDefault();
  const lat = document.getElementById("lat").value;
  const lon = document.getElementById("lon").value;
  displayWeatherData(lat, lon);
});



window.onload = async () => {
  const latestSearch = await getLatestSearch();
  if (latestSearch) {
    const { lat, lon, approvedTime, hourlyData } = latestSearch;

    approvedTimeElement.innerHTML = `Approved time: ${formatDateTime(approvedTime)}<br/> Longitude: ${lon}<br/> Latitude: ${lat}`;
    
    weatherDataElement.innerHTML = "";
  
    for (const data of hourlyData) {
      const row = weatherDataElement.insertRow();
      const timeCell = row.insertCell(0);
      const tempCell = row.insertCell(1);
      const iconCell = row.insertCell(2);
  
      const dayOrNight = getTime(data.time);

      timeCell.textContent = data.time;
      tempCell.textContent = data.temperature;
      iconCell.innerHTML = data.icon;
    }
  }
}; 


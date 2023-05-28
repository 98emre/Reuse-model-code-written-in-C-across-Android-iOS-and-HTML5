
const inputForm = document.getElementById("inputForm");
const latInput = document.getElementById("lat");
const lonInput = document.getElementById("lon");
const approvedTimeElement = document.getElementById("approvedTime");
const weatherDataElement = document.getElementById("weatherData").getElementsByTagName("tbody")[0];


const weather = new WeatherData()
const hourly = new HourlyData()

const displayWeather = async (lat, lon) => {
    try {
        const data = await fetchWeatherData(lat,lon)

        approvedTimeElement.innerHTML = `Approved time: ${formatDateTime(data.approvedTime)} <br/> Longitude: ${lon}<br/> Latitude: ${lat}`;
        weatherDataElement.innerHTML = ''; 
        
        weather.setApprovedTime(formatDateTime(data.approvedTime))

        const weatherViewModel = new WeatherDataViewModel(weather)
        weatherViewModel.updateLocation(lat,lon)
        const hourlyDataToSave = []; // Array to store all time series data

        data.timeSeries.forEach(data => {
            let hourlyDataEntry = {}; // Create a new object reference in each iteration

            const time = formatDateTime(data.validTime);
            const temperature = data.parameters.find(param => param.name === 't').values[0];
            const weatherNumSymbol = data.parameters.find(param => param.name === "Wsymb2").values[0];
            const dayOrNight = getDayOrNight(time);
            const icon = `<img src="./weather_symbols/${dayOrNight}/${dayOrNight}${weatherNumSymbol}.png" alt="Weather Icon">`;
        
            hourly.createHourlyData(time,temperature,icon)
            const hourlyViewModel = new HourlyDataViewModel(hourly)
            weatherViewModel.addHourlyData(hourlyViewModel.getTime(),hourlyViewModel.getTemperature(),hourlyViewModel.getIcon())

            hourlyDataEntry = { time: hourlyViewModel.getTime(), temperature: hourlyViewModel.getTemperature(), icon: hourlyViewModel.getIcon() };
            hourlyDataToSave.push(hourlyDataEntry);

            const row = weatherDataElement.insertRow();
            row.insertCell(0).textContent = hourlyViewModel.getTime();
            row.insertCell(1).textContent = hourlyViewModel.getTemperature();
            row.insertCell(2).innerHTML = hourlyViewModel.getIcon();
        })
    
        saveLatestSearch(weatherViewModel.getLat(), weatherViewModel.getLon(), {
          approvedTime: weatherViewModel.getApprovedTime(),
          hourlyData: hourlyDataToSave,
        });    
    
    } 

    catch (error) {
        console.error(error);
        alert("Failed to fetch weather data.");
    };
}

inputForm.addEventListener("submit", event => {
    event.preventDefault();
    const lat = latInput.value;
    const lon = lonInput.value;
    displayWeather(lat, lon);
});



window.onload = async () => {
    const latestSearch = await getLatestSearch();
    
    if (latestSearch) {
      const { lat, lon, approvedTime, hourlyData } = latestSearch;
  
      approvedTimeElement.innerHTML = `Approved time: ${formatDateTime(approvedTime)}<br/> Longitude: ${lon}<br/> Latitude: ${lat}`;
      
      weatherDataElement.innerHTML = "";
  
      if (Array.isArray(hourlyData)) {
        for (const data of hourlyData) {
          const row = weatherDataElement.insertRow();
          const timeCell = row.insertCell(0);
          const tempCell = row.insertCell(1);
          const iconCell = row.insertCell(2);
      
          const dayOrNight = getDayOrNight(data.time);
    
          timeCell.textContent = data.time;
          tempCell.textContent = data.temperature;
          iconCell.innerHTML = data.icon;
        }
      }
    }
  };
  
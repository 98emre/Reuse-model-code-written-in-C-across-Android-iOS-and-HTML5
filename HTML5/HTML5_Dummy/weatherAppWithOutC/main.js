


const inputForm = document.getElementById("inputForm");
const latInput = document.getElementById("lat");
const lonInput = document.getElementById("lon");
const approvedTimeElement = document.getElementById("approvedTime");
const weatherDataElement = document.getElementById("weatherData").getElementsByTagName("tbody")[0];

const dummyWeatherData = [
    {
      approvedTime: "2023-04-30 23:00",
      lat: 59.3293,
      lon: 18.0686,
      hourlyData: [
        { time: "2023-05-01 00:00", temperature: "2°C", icon: "Cloud.png" }
      ]
    }
  ];


  const weather = new WeatherData()
  const hourlyData = new HourlyData()

  function displayWeatherData(lon,lat) {
    try{

      weather.setApprovedTime("2022-05-10 12:00")
      const weatherViewModel = new WeatherDataViewModel(weather)
      weatherViewModel.updateLocation(latInput.value,lonInput.value)

      approvedTimeElement.innerHTML = 
          `Approved time: ${formatDateTime(weatherViewModel.getApprovedTime())} 
          <br/> Longitude: ${weatherViewModel.getLon()}
          <br/> Latitude: ${weatherViewModel.getLat()}`;
    
      weatherDataElement.innerHTML = "";

      hourlyData.createHourlyData(
          dummyWeatherData[0].hourlyData[0].time,
          dummyWeatherData[0].hourlyData[0].temperature,
          dummyWeatherData[0].hourlyData[0].icon
      )

      const hourlyViewModel = new HourlyDataViewModel(hourlyData)

      for(let i = 0; i<100; i++){
        weatherViewModel.addHourlyData(hourlyViewModel.getTime(),hourlyViewModel.getTemperature(),hourlyViewModel.getIcon())
      }

      for (let i = 0; i < weatherViewModel.getHourlyDataSize(); i++) {    
        const row = weatherDataElement.insertRow();
        const timeCell = row.insertCell(0);
        const tempCell = row.insertCell(1);
        const iconCell = row.insertCell(2);
      
        timeCell.textContent = weatherViewModel.getHourlyData(i).getTime();
        tempCell.textContent = weatherViewModel.getHourlyData(i).getTemperature();
        iconCell.innerHTML = weatherViewModel.getHourlyData(i).getIcon();
      }
        
    } catch(error){
        console.log("Error " + error)
    }
  }

  const form = document.getElementById("inputForm");
    form.addEventListener("submit", async (event) => {
        event.preventDefault();
        const lat = latInput.value;
        const lon = lonInput.value;
        displayWeatherData(lat, lon);
});

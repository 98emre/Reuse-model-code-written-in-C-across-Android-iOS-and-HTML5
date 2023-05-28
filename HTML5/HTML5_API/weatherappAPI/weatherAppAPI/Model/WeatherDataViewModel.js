
class WeatherDataViewModel {
    constructor(weatherData) {
      this.weatherData = weatherData
    }
  
    getApprovedTime() {
      return this.weatherData.getApprovedTime();
    }
  
    getLat() {
      return this.weatherData.getLat();
    }
  
    getLon() {
      return this.weatherData.getLon();
    }
  
    addHourlyData(time, temperature, icon) {
      const hourlyData = new HourlyData();
      hourlyData.createHourlyData(time, temperature, icon);
      this.weatherData.addHourlyData(hourlyData);
    }
  
    getHourlyData(index) {
      const hourlyData = this.weatherData.getHourlyData(index);
  
      if (!hourlyData) {
        return null;
      }
  
      const hourlyViewModel = new HourlyDataViewModel(hourlyData);
      return hourlyViewModel;
    }
  
    getHourlyDataSize() {
      return this.weatherData.getHourlyDataSize();
    }
  
    updateLocation(lat,lon){
      this.weatherData.setLat(lat)
      this.weatherData.setLon(lon)
    }

  }
  
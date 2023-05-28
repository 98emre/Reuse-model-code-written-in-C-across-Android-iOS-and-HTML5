
class HourlyDataViewModel {
  constructor(hourlyData) {
    this.hourlyData = hourlyData;
  }

  getTime() {
    return this.hourlyData.getTime();
  }

  getTemperature() {
    return this.hourlyData.getTemperature();
  }

  getIcon() {
    return this.hourlyData.getIcon();
  }

  freeHourlyObject() {
    this.hourlyData.freeHourlyWeatherObject();
  }
}

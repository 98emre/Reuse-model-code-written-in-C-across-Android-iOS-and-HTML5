
class HourlyData {
    time;
    temperature;
    icon;

    createHourlyData(time, temperature, icon) {
      this.time = time;
      this.temperature = temperature;
      this.icon = icon;
    }
  
    getTime() {
      return this.time;
    }
  
    getTemperature() {
      return this.temperature;
    }
  
    getIcon() {
      return this.icon;
    }
  }
  
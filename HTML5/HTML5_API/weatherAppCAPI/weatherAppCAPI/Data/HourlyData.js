

    class HourlyData {
      time;
      temperature;
      icon;
      hourlyDataObj = null; 

      createHourlyWeatherObject(time, temperature, icon) {
        this.hourlyDataObj = Module.ccall("createHourlyWeatherObjectFromCWrapper", "number", ["string", "string", "string"],[time, temperature, icon]);
      }

      getTime() {
        this.time = Module.ccall("getTimeWrapper", "string", ["number"], [this.hourlyDataObj]);
        return this.time;
      }
      
      getTemperature() {
        this.temperature = Module.ccall("getTemperatureWrapper", "string", ["number"], [this.hourlyDataObj]);
        return this.temperature;
      }
      
      getIcon() {
        this.icon = Module.ccall("getIconWrapper", "string", ["number"], [this.hourlyDataObj]);
        return this.icon;
      }
      
      setTime(time) {
        Module.ccall("setTimeWrapper", null, ["number", "string"], [this.hourlyDataObj, time]);
      }

      setTemperature(temperature) {
        Module.ccall("setTemperatureWrapper", null, ["number", "string"], [this.hourlyDataObj, temperature]);
      }

      setIcon(icon) {
        Module.ccall("setIconWrapper", null, ["number", "string"], [this.hourlyDataObj, icon]);
      }

      freeHourlyWeatherObject() {
        Module.ccall("freeHourlyWeatherObjectWrapper", null, ["number"], [this.hourlyDataObj]);
      }
    }


    
    
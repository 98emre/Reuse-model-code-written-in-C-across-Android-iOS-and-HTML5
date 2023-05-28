
      
      class WeatherData {
        approvedTime; 
        size = 0;
        lat = 0;
        lon = 0;
        weatherObj = null;

        createWeatherObject(approvedTime) {
          this.weatherObj = Module.ccall(  "createWeatherObjectFromCWrapper","number", ["string"], [approvedTime]);
        }

        getApprovedTime() {
          this.approvedTime = Module.ccall("getApprovedTimeWrapper", "string", ["number"], [this.weatherObj]);
          return this.approvedTime;
        }

        setApprovedTime(approvedTime){
          Module.ccall("setApprovedTimeWrapper", null, ["number", "string"], [this.weatherObj, approvedTime]);
        }

        getLat() {
          this.lat = Module.ccall("getLatWrapper","number", ["number"], [this.weatherObj]);
          return this.lat
        }

        setLat(lat) {
          Module.ccall("setLatWrapper", null, ["number", "number"], [this.weatherObj, lat]);
        }

        getLon() {
          this.lon = Module.ccall("getLonWrapper","number", ["number"], [this.weatherObj]);
          return this.lon;
        }

        setLon(lon) {
          Module.ccall("setLonWrapper", null, ["number", "number"], [this.weatherObj, lon]);
        }

        addHourlyData(hourlyData) {
          this.size++;
          Module.ccall("addHourlyDataWrapper",null,["number", "number"],[this.weatherObj, hourlyData.hourlyDataObj]);
        }

        getHourlyData(index) {
          if (index < 0 || index >= this.getHourlyDataSize()) {
            return null;
          }

          const hourlyDataObj = Module.ccall("getHourlyDataWrapper", "number", ["number", "number"],[this.weatherObj, index]);

          const hourlyData = new HourlyData();
          hourlyData.hourlyDataObj = hourlyDataObj;
          return hourlyData;
        }

        getHourlyDataSize() {
          return Module.ccall("getHourlyDataSizeWrapper","number",["number"],[this.weatherObj]);
        }
                 
        freeWeatherObject() {
          Module.ccall("freeWeatherObjectWrapper", null, ["number"], [this.weatherObj]);
        }
      }



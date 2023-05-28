
class WeatherData {
  approvedTime; 
  size = 0;
  lat = 0;
  lon = 0;
  data = []

  getApprovedTime() {
    return this.approvedTime;
  }

  setApprovedTime(approvedTime) {
    this.approvedTime = approvedTime;
  }

  getLat() {
    return this.lat;
  }

  setLat(lat) {
    this.lat = lat;
  }

  getLon() {
    return this.lon;
  }

  setLon(lon) {
    this.lon = lon;
  }

  addHourlyData(hourlyData) {
    if (hourlyData !== null && hourlyData !== undefined) {
      this.data.push(hourlyData);
      this.size++;
    }
  }
  

  getHourlyDataSize() {
    return this.size;
  }

  getHourlyData(index) {
    if (index < 0 || index >= this.size) {
      return null;
    }
    return this.data[index];
  }
}

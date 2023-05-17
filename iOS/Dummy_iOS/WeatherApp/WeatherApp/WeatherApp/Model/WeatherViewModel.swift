import Foundation

class WeatherViewModel: ObservableObject {
    @Published var weather: Weather

    init(weather: Weather) {
        self.weather = weather
    }
    
    func appendWeatherData(hourlyData: HourlyWeather) {
        weather.appendHourlyData(hourlyData: hourlyData)
    }

    func weatherData(at index: Int) -> HourlyWeather? {
        return weather.hourlyData(at: index)
    }

    var size: Int {
        return weather.size
    }
    
    func updateLocation(latitude: Float, longitude: Float) {
        weather.latitude = latitude
        weather.longitude = longitude
    }
    
    var latitude: Float {
        return weather.latitude
    }

    var longitude: Float {
        return weather.longitude
    }
    var approvedTime: String {
        return weather.approvedTime
    }
    
    func updateApprovedTime(approvedTime: String) {
        weather.approvedTime = approvedTime
    }
}








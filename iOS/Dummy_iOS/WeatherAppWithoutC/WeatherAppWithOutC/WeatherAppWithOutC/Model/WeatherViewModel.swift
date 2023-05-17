import Foundation

class WeatherViewModel: ObservableObject {
    @Published var weather: Weather

    init(weather: Weather) {
        self.weather = weather
    }

    func appendHourlyWeather(hourlyWeather: HourlyWeather) {
        weather.hourlyWeathers.append(hourlyWeather)
    }

    func hourlyWeather(at index: Int) -> HourlyWeather? {
        if index < 0 || index >= weather.hourlyWeathers.count {
            return nil
        }
        return weather.hourlyWeathers[index]
    }

    var hourlyWeathersSize: Int {
        return weather.hourlyWeathers.count
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

    func updateApprovedTime(approvedTime: String) {
        weather.approvedTime = approvedTime
    }

    var approvedTime: String {
        return weather.approvedTime
    }

    func updateHourlyWeathers(hourlyWeathers: [HourlyWeather]) {
        weather.hourlyWeathers = hourlyWeathers
    }
}

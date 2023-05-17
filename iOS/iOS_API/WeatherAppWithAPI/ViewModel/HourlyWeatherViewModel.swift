
import Foundation

struct HourlyWeatherViewModel {
    let hourlyWeather: HourlyWeatherData

    var time: String {
        return hourlyWeather.time
    }

    var temperature: String {
        return hourlyWeather.temperature
    }

    var icon: String {
        return hourlyWeather.icon
    }
}

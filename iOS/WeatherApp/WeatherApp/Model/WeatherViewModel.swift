import Foundation

struct WeatherViewModel {
    let weather: Weather
    
    var temperature: String {
        return weather.temperature
    }

    var weekDay: String {
        return weather.weekDay
    }

    var loadData: Bool {
        return weather.loadData
    }

    var date: String {
        return weather.date
    }

    var prognosImage: String {
        return weather.prognosImage
    }
}

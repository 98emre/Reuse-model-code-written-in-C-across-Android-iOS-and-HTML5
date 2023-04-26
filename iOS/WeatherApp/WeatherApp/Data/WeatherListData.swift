import Foundation

class WeatherListData {
    var data: UnsafeMutablePointer<WeatherList>

    init(cityName: String, capacity: Int) {
        data = createWeatherList(cityName, Int32(capacity))
    }
    
    var cityName: String {
        get {
            return String(cString: getCityName(data))
        }
        set {
            setCityName(data, newValue)
        }
    }

    func appendWeatherData(weather: Weather) {
        let copiedWeatherData = createWeatherObjectFromC(weather.temperature, weather.weekDay, weather.loadData, weather.date, weather.prognosImage)
        addWeatherData(data, copiedWeatherData)
    }

    func weatherData(at index: Int) -> Weather? {
        if let weatherData = getWeatherData(data, Int32(index)) {
            return Weather(data: weatherData)
        }
        return nil
    }
     
    var size: Int {
        return Int(getWeatherListSize(data))
    }
}

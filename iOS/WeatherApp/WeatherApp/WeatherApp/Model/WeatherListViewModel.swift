import SwiftUI

class WeatherListViewModel: ObservableObject {
    @Published var weatherList: WeatherListData

    init(weatherList: WeatherListData) {
        self.weatherList = weatherList
    }
    
    func appendWeatherData(weather: Weather) {
        weatherList.appendWeatherData(weather: weather)
    }

    func weatherData(at index: Int) -> Weather? {
        return weatherList.weatherData(at: index)
    }

    var size: Int {
        return weatherList.size
    }
}

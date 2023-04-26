import Foundation

class WeatherListViewModel: ObservableObject {
    @Published var weatherList: WeatherListData

    init(weatherList: WeatherListData) {
        self.weatherList = weatherList
    }

    func appendWeatherData(weather: Weather) {
        weatherList.weathers.append(weather)
    }

    func weatherData(at index: Int) -> Weather? {
        if index < 0 || index >= weatherList.weathers.count {
            return nil
        }
        return weatherList.weathers[index]
    }

    var size: Int {
        return weatherList.weathers.count
    }
}

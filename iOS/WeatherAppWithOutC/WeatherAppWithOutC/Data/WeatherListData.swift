import Foundation

struct WeatherListData {
    private var _cityName: String
    private var _weathers: [Weather]
    
    init(cityName: String, weathers: [Weather]) {
        _cityName = cityName
        _weathers = weathers
    }
    
    var cityName: String {
        get { return _cityName }
        set { _cityName = newValue }
    }
    
    var weathers: [Weather] {
        get { return _weathers }
        set { _weathers = newValue }
    }
}

import Foundation


// Weather Data

struct WeatherData: Decodable, Identifiable {
    var _id = UUID()
    private var _approvedTime: String
    private var _hourlyWeathers: [HourlyWeatherData]
    private var _latitude: Double
    private var _longitude: Double

    init(_ approvedTime: String, _ hourlyWeathers: [HourlyWeatherData], _ latitude: Double, _ longitude: Double) {
        self._approvedTime = approvedTime
        self._hourlyWeathers = hourlyWeathers
        self._latitude = latitude
        self._longitude = longitude
    }
    
    var id: UUID {
         return _id
    }

    var approvedTime: String {
        get {
            return _approvedTime
        }
        set {
            _approvedTime = newValue
        }
    }

    var getAllHourlyData: [HourlyWeatherData] {
        get {
            return _hourlyWeathers
        }
        set {
            _hourlyWeathers = newValue
        }
    }

    var latitude: Double {
        get {
            return _latitude
        }
        set {
            _latitude = newValue
        }
    }

    var longitude: Double {
        get {
            return _longitude
        }
        set {
            _longitude = newValue
        }
    }
}

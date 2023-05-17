import Foundation

class Weather {
    private var _approvedTime: String
    private var _hourlyWeathers: [HourlyWeather]
    private var _latitude: Float
    private var _longitude: Float

    init(approvedTime: String, hourlyWeathers: [HourlyWeather], latitude: Float, longitude: Float) {
        self._approvedTime = approvedTime
        self._hourlyWeathers = hourlyWeathers
        self._latitude = latitude
        self._longitude = longitude
    }

    var approvedTime: String {
        get {
            return _approvedTime
        }
        set {
            _approvedTime = newValue
        }
    }

    var hourlyWeathers: [HourlyWeather] {
        get {
            return _hourlyWeathers
        }
        set {
            _hourlyWeathers = newValue
        }
    }

    var latitude: Float {
        get {
            return _latitude
        }
        set {
            _latitude = newValue
        }
    }

    var longitude: Float {
        get {
            return _longitude
        }
        set {
            _longitude = newValue
        }
    }
}

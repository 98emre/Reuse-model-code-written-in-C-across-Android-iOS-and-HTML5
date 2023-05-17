import Foundation


// Hourly Weather Data

struct HourlyWeatherData: Decodable, Identifiable, Hashable {
    private var _id = UUID()
    private var _temperature: String
    private var _time: String
    private var _icon: String

    init(temperature: String, time: String, icon: String) {
        self._temperature = temperature
        self._time = time
        self._icon = icon
    }
    
    var temperature: String {
        get {
            return _temperature
        }
        set {
            _temperature = newValue
        }
    }

    var time: String {
        get {
            return _time
        }
        set {
            _time = newValue
        }
    }

    var icon: String {
        get {
            return _icon
        }
        set {
            _icon = newValue
        }
    }
    
    var id: UUID {
        return _id
    }

}

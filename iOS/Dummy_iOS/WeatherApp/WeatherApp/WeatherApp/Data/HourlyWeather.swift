import Foundation

struct HourlyWeather {
    var data: UnsafeMutablePointer<HourlyWeatherData>
    
    init(data: UnsafeMutablePointer<HourlyWeatherData>) {
            self.data = data
    }
    
    init(time: String, temperature: String, icon: String) {
        data = createHourlyWeatherObjectFromC(time, temperature, icon)
    }
    
    var time: String {
        get {
            return String(cString: getTime(data))
        }
        
        set {
            setTime(data, newValue)
        }
    }
    
    var temperature: String {
        get {
            return String(cString: getTemperature(data))
        }
        
        set {
            setTemperature(data, newValue)
        }
    }
    
    var icon: String {
        get {
            return String(cString: getIcon(data))
        }
        
        set {
            setIcon(data, newValue)
        }
    }
}

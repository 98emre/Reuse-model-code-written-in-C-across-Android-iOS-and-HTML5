import Foundation

// Weather Data


class Weather {
    
    var data: UnsafeMutablePointer<WeatherData>
    
    init(approvedTime: String, latitude: Float, longitude: Float) {
           data = createWeatherObjectFromC(approvedTime)
           setLat(data, latitude)
           setLon(data, longitude)
    }
    
    deinit {
        freeWeatherObject(data)
    }
        
    var approvedTime: String {
        get {
            return String(cString: getApprovedTime(data))
        }
        
        set {
            setApprovedTime(data, newValue)
        }
    }
    
    var hourlyDataSize: Int {
        return Int(getHourlyDataSize(data))
    }
    
    var latitude: Float {
        get {
            return getLat(data)
        }
        
        set {
            setLat(data, newValue)
        }
    }
    
    var longitude: Float {
        get {
            return getLon(data)
        }
     
        set {
            setLon(data, newValue)
        }
    }
    
    func appendHourlyData(hourlyData: HourlyWeather) {
        let copiedHourlyData = createHourlyWeatherObjectFromC(hourlyData.time, hourlyData.temperature, hourlyData.icon)
        addHourlyData(data, copiedHourlyData)
        freeHourlyWeatherObject(copiedHourlyData)
    }
    
    func hourlyData(at index: Int) -> HourlyWeather? {
        if let hourlyData = getHourlyData(data, Int32(index)) {
            return HourlyWeather(data: hourlyData)
        }
        return nil
    }
    
    var size: Int {
        return Int(getHourlyDataSize(data))
    }
}

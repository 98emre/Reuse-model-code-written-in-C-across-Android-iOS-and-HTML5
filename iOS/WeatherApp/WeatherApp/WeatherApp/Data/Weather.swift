import Foundation

    class Weather {
        var data: UnsafeMutablePointer<WeatherData>
        
        init(data: UnsafeMutablePointer<WeatherData>) {
                self.data = data
        }

        init(temperature: String, weekDay: String, loadData: Bool, date: String, prognosImage: String) {
            data = createWeatherObjectFromC(temperature, weekDay, loadData, date, prognosImage)
        }
        
    
    var temperature: String {
        get {
            return String(cString: getTemperature(data))
        }
            
        set {
            setTemperature(data, newValue)
        }
    }

    var weekDay: String {
        get {
            return String(cString: getWeekDay(data))
        }
        
        set {
            setWeekDay(data, newValue)
        }
    }


    var loadData: Bool {
        get {
            return getLoadData(data)
        }
        
        set {
            setLoadData(data, newValue)
        }
    }

    var date: String {
        get {
            return String(cString: getDate(data))
        }
        set {
            setDate(data, newValue)
        }
    }

    var prognosImage: String {
        get {
            return String(cString: getPrognosImage(data))
        }
        set {
            setPrognosImage(data, newValue)
        }
    }
}

import Foundation

struct WeatherData: Identifiable {
    // Generarar en unik ID som använder UUID
    let id = UUID()
    let cityName: String // Name av staden
    let temperature: String // Temperaturen
    let weekDay: String // weekodagen
    let loadData: Bool // Om data är laddad
    let date: String // visar datum
    let prognosImage: String // vad för typ av prognos image
}

class WeatherWrapper {
    
    func createWeatherObject(cityName: String, temperature: String, weekDay: String,
                             loadData: Bool, date: String, prognosImage: String) ->  WeatherData{
        
        let weatherDataPtr = createWeatherObjectFromC(
            cityName.cString(using: .utf8),
            temperature.cString(using: .utf8),
            weekDay.cString(using: .utf8),
            loadData,
            date.cString(using: .utf8),
            prognosImage.cString(using: .utf8)
        ) // Skapar objekt från C kod
        
        let weatherData = WeatherData(
            cityName: String(cString: getCityName(weatherDataPtr)),
            temperature: String(cString: getTemperature(weatherDataPtr)),
            weekDay: String(cString: getWeekDay(weatherDataPtr)),
            loadData: getLoadData(weatherDataPtr),
            date: String(cString: getDate(weatherDataPtr)),
            prognosImage: String(cString: getPrognosImage(weatherDataPtr))
        )

        freeWeatherObject(weatherDataPtr) // Fri gör minnet allokering från objketen i C koden
        
        return weatherData
    }
}

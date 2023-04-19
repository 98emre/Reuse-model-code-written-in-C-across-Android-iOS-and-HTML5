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

// Definiera en DummyWeatherData klass som håller testdata för appen
// Klassen används för att lagra testdata för appen


class DummyData{
    var weatherObjects: [WeatherData] = []


    let dummyData = [
        ("Stockholm", "-1 °C", "Mon", true, "2023-03-27", "snowflake"),
        ("Stockholm", "3 °C", "Tues", true, "2023-03-28", "cloud"),
        ("Stockholm", "10 °C", "Wed", true, "2023-03-29", "sun.min"),
        ("Stockholm", "-1 °C", "Mon", true, "2023-03-30", "snowflake"),
        ("Stockholm", "3 °C", "Tues", true, "2023-03-31", "cloud"),
        ("Stockholm", "10 °C", "Wed", true, "2023-04-01", "sun.min"),
        ("Stockholm", "-1 °C", "Mon", true, "2023-03-27", "snowflake"),
        ("Stockholm", "3 °C", "Tues", true, "2023-03-28", "cloud")
    ]
    
    // Konstruktor för att fylla weatherObjects med testdata

    init() {
        // Skapa ett WeatherData-objekt för varje element i dummyData och lägg till objektet i weatherObjects
        for data in dummyData {
            let weatherData = WeatherData(
                cityName: data.0,
                temperature: data.1,
                weekDay: data.2,
                loadData: data.3,
                date: data.4,
                prognosImage: data.5)
            
            weatherObjects.append(weatherData)
        }
    }
}

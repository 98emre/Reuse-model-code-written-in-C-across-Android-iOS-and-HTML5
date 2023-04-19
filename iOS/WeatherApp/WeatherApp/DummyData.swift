import Foundation

// Definiera en DummyWeatherData klass som håller testdata för appen
// Klassen används för att lagra testdata för appen

class DummyWeatherData {
    // Skapa en instans av WeatherWrapper för att skapa WeatherData-objekt
    let weatherDataWrapper = WeatherWrapper()
    var weatherObjects: [WeatherData] = []

    // Konstruktor för att fylla weatherObjects med testdata
    init() {
        let dummyData = [
            ("Stockholm", "-1 °C", "Mon", true, "2023-03-27", "snowflake"),
            ("Stockholm", "3 °C", "Tues", true, "2023-03-28", "cloud"),
            ("Stockholm", "10 °C", "Wed", true, "2023-03-29", "sun.min"),
            ("Stockholm", "-1 °C", "Mon", true, "2023-03-30", "snowflake"),
            ("Stockholm", "3 °C", "Tues", true, "2023-03-31", "cloud"),
            ("Stockholm", "10 °C", "Wed", true, "2023-04-01", "sun.min")
        ]

        // Skapa ett WeatherData-objekt för varje element i dummyData och lägg till objektet i weatherObjects
        for data in dummyData {
            let weatherData = weatherDataWrapper.createWeatherObject(
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


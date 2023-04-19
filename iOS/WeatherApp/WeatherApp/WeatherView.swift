import SwiftUI

// Definiera WeatherView structen som anpassar sig till View protokollet
struct WeatherView: View {
    
    // Skapa en instans av DummyWeatherData för att hämta testdata
    private let dummyWeatherData = DummyWeatherData()

    // Definiera "body" variabeln som returnerar en NavigationView med en lista av väderobjekt
    var body: some View {
        NavigationView {
            // Lista av väderobjekt
            List(dummyWeatherData.weatherObjects) { weatherData in
                // HStack för att placera innehåll horisontellt
                HStack {
                    // VStack för att placera innehåll vertikalt
                    VStack(alignment: .leading) {
                        Text(weatherData.cityName)
                            .font(.headline)
                        Text(weatherData.date)
                            .font(.subheadline)
                    }
                    
                    // Spacer för att skapa utrymme mellan element
                    Spacer()
                    
                    Text(weatherData.weekDay)
                        .font(.body)
                        .fontWeight(.bold)
                        .padding()
                    
                    Spacer()
                    
                    Text(weatherData.temperature)
                        .font(.headline)
                    
                    // Image för att visa prognosbild
                    Image(systemName: weatherData.prognosImage)
                        .resizable()
                        .aspectRatio(contentMode: .fit)
                        .frame(width: 40, height: 40)
                        .padding()
                }
            }
            // Navigation Title för att sätta titeln på vyn
            .navigationTitle("Väder")
        }
    }
}

// Definiera WeatherView_Previews structen som anpassar sig till PreviewProvider protokollet
struct WeatherView_Previews: PreviewProvider {
    
    // Definiera "previews" variabeln som returnerar en vy som visar "WeatherView"
    static var previews: some View {
        WeatherView() // Visa vyn "WeatherView"
    }
}



import SwiftUI

// Definiera WeatherView structen som anpassar sig till View protokollet
struct WeatherView: View {
    
    // Skapa en instans av DummyData för att hämta testdata
    private let dummyData = DummyData()

    
    // Definiera "body" variabeln som returnerar en NavigationView med en lista av väderobjekt
    var body: some View {
        NavigationView {
            
            // Lista av väderobjekt
                List(dummyData.weatherObjects){ data in
                        // HStack för att placera innehåll horisontellt
                        HStack{
                            
                            // VStack för att placera innehåll vertikalt
                            VStack(alignment: .leading){
                                Text(data.cityName).font(.headline)
                                Text(data.date).font(.subheadline)
                            }
                            
                            // Image för att visa prognosbild
                            Spacer()
                            Text(data.weekDay)
                                .font(.body)
                                .fontWeight(.bold)
                                .padding()
                            
                            Spacer()
                            Text(data.temperature)
                                .font(.headline)
                            
                            // Image för att visa prognosbild
                            Image(systemName: data.prognosImage)
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

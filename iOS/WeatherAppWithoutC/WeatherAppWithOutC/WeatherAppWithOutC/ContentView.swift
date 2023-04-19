import SwiftUI

// Definiera ContentView structen som anpassar sig till View protokollet
struct ContentView: View {
    
    // Definiera "body" variabeln som returnerar en vy som visar "WeatherView"
    var body: some View {
        WeatherView() // Visa vyn "WeatherView"
    }
}

// Definiera ContentView_Previews structen som anpassar sig till PreviewProvider protokollet
struct ContentView_Previews: PreviewProvider {
    
    // Definiera "previews" variabeln som returnerar en vy som visar "ContentView"
    static var previews: some View {
        ContentView() // Visa vyn "ContentView"
    }
}



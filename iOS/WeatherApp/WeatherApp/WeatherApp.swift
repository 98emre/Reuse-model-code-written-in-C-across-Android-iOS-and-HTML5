import SwiftUI

// Structen definierar en ny app med namnet "WeatherApp" med hjälp av @main attributet
// Structen anpassar sig till "App" protokollet som definierar appens livscykel
@main
struct WeatherApp: App {
    
    // body" variabeln definierar appens huvudvy som visas i en "WindowGroup
    // det retunrerar  en vy som visar huvudvyn "ContentView"
    var body: some Scene {
        WindowGroup {
            ContentView() // Visa huvudvy för appen
        }
    }
}

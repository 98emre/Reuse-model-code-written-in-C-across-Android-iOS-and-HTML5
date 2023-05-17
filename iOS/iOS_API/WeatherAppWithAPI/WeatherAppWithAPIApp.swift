import SwiftUI

@main
struct WeatherAppWithAPIApp: App {
    @StateObject private var dataController = DataController()
    
    
    var body: some Scene {
        WindowGroup {
            ContentView()
              //.environment(\.managedObjectContext, dataController.container.viewContext)
             // .environmentObject(DataController())
        }
    }
}


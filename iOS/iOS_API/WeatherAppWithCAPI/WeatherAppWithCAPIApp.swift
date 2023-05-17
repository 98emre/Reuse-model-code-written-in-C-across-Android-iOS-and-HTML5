import SwiftUI

@main
struct WeatherAppWithCAPIApp: App {
    @StateObject private var dataController = DataController()

    
    var body: some Scene {
        WindowGroup {
            ContentView()
                .environment(\.managedObjectContext, dataController.container.viewContext)
                .environmentObject(DataController())
        }
    }
}

import SwiftUI

import SwiftUI

struct ContentView: View {
    var body: some View {
        WeatherView()
    }
}



struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
           .environmentObject(DataController())
    }
}

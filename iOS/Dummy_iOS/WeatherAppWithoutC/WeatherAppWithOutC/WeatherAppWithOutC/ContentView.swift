import SwiftUI

struct ContentView: View {

    var body: some View {
        WeatherView(weatherViewModel: WeatherViewModel(weather: Weather(approvedTime: "", hourlyWeathers: [], latitude: 0.0, longitude: 0.0)))
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}



import SwiftUI

struct ContentView: View {
    var weatherViewModel: WeatherViewModel =
    WeatherViewModel(weather: Weather(approvedTime: "2022-05-15 22:00", latitude: 10, longitude: 60))
    
    var body: some View {
        WeatherView(weatherViewModel: weatherViewModel)
    }
}

struct ContentView_Previews: PreviewProvider {
    
    static var previews: some View {
        ContentView()
    }
}



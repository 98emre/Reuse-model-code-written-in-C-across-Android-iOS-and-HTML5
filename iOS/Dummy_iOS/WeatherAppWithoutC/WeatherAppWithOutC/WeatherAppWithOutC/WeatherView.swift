import SwiftUI

struct WeatherView: View {
    @ObservedObject var weatherViewModel: WeatherViewModel
    @State private var latitude: String = ""
    @State private var longitude: String = ""
    @State private var showList: Bool = false
    
    var body: some View {
        NavigationView {
            VStack {
                if showList {
                    List {
                        ForEach(0..<weatherViewModel.hourlyWeathersSize, id: \.self) { index in
                            if let hourlyWeather = weatherViewModel.hourlyWeather(at: index) {
                                let hourlyWeatherViewModel = HourlyWeatherViewModel(hourlyWeather: hourlyWeather)
                                HourlyWeatherRow(viewModel: hourlyWeatherViewModel)
                            }
                        }
                    }
                    .listStyle(GroupedListStyle())
                } else{
                    Text("Tryck submit för att visa dummy lista")
                }
                
                HStack {
                    TextField("Latitude", text: $latitude)
                        .textFieldStyle(RoundedBorderTextFieldStyle())
                        .padding()
                    
                    TextField("Longitude", text: $longitude)
                        .textFieldStyle(RoundedBorderTextFieldStyle())
                        .padding()
                }
                
                Button("Submit") {
                    if(!showList){
                        generateDummyData(weather: weatherViewModel)
                    }
                    showList = true
                }
            }
            .navigationTitle("Weather Forecast Dummy")
            .navigationBarTitleDisplayMode(.inline)
        }
    }
    
    func generateDummyData(weather: WeatherViewModel) {
        for _ in 0..<100 {
            let hourlyWeather = HourlyWeather(temperature: "10C", time: "2022-05-15 22:00", icon: "1")
            weather.appendHourlyWeather(hourlyWeather: hourlyWeather)
        }
    }
}

struct HourlyWeatherRow: View {
    let hourlyWeatherViewModel: HourlyWeatherViewModel
    
    init(viewModel: HourlyWeatherViewModel) {
        self.hourlyWeatherViewModel = viewModel
    }
    
    var body: some View {
        VStack {
            Text(hourlyWeatherViewModel.time)
                .fontWeight(.light)
                .font(.subheadline)
            HStack {
                Text(hourlyWeatherViewModel.temperature + " °C")
                    .fontWeight(.medium)
                    .font(.title3)
                Image(systemName: hourlyWeatherViewModel.icon)
                    .resizable()
                    .scaledToFit()
                    .frame(width: 30, height: 30)
            }
        }
    }
}

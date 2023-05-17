import SwiftUI

struct WeatherView: View {
    @ObservedObject var weatherViewModel: WeatherViewModel
    @State var latitude: String = ""
    @State var longitude: String = ""
    @State var showList: Bool = false
    
    var body: some View {
        NavigationView {
            VStack {
                if showList {
                    List {
                        ForEach(0..<weatherViewModel.size, id: \.self) { index in
                            if let hourlyWeather = weatherViewModel.weatherData(at: index) {
                                let hourlyWeatherViewModel = HourlyWeatherViewModel(hourlyWeather: hourlyWeather)
                                HourlyWeatherRow(viewModel: hourlyWeatherViewModel)
                            }
                        }
                    }
                    .listStyle(GroupedListStyle())
                } else {
                    Text("Tryck submit för att hämta dummy data")
                    EmptyView()
                }
                
                HStack {
                    TextField("Latitude", text: $latitude)
                        .textFieldStyle(RoundedBorderTextFieldStyle())
                        .padding()
                    
                    TextField("Longitude", text: $longitude)
                        .textFieldStyle(RoundedBorderTextFieldStyle())
                        .padding()
                    
                    Button("Submit") {
                        weatherViewModel.updateLocation(latitude: 10, longitude: 60)
                        
                        if(!showList){
                            generateDummyData() // Generera dummydata när submit-knappen trycks

                        }
                        
                        showList = true
                    }
                    .padding()
                    .background(Color.blue)
                    .foregroundColor(.white)
                    .cornerRadius(10)
                }
            }
            .navigationTitle("Weather Forecast C Dummy")
        }
    }
    
    // Funktion för att generera dummydata
    func generateDummyData() {
        let dummyDataGenerator = DummyDataGenerator()
        dummyDataGenerator.generateDummyData(weather: weatherViewModel.weather)
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

class DummyDataGenerator {
    func generateDummyData(weather: Weather) {
        for _ in 0..<100 {
            let hourlyWeather = HourlyWeather(time: "2022-05-15 18:00", temperature: "10 C", icon: "1")
            weather.appendHourlyData(hourlyData: hourlyWeather)
        }
    }
}

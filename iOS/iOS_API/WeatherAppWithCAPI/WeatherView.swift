import SwiftUI

struct WeatherView: View {
    
    
    @StateObject private var weatherViewModel: WeatherViewModel
                = WeatherViewModel(Weather(approvedTime: "",latitude: 0.0, longitude: 0.0), DataController())
    
    @State private var latitude: String = ""
    @State private var longitude: String = ""
    @State private var showError: Bool = false
    @State private var errorMessage: String = ""
    
    var body: some View {
        NavigationView {
            VStack {
                List {
                    if weatherViewModel.size > 0 {
                        Text("Approved Time: \(formatTimeString(weatherViewModel.approvedTime))")
                            .font(.headline)
                            .padding(.bottom)
                        Text("Longitude: \(weatherViewModel.longitude)\n" +
                             "Latitude: \(weatherViewModel.latitude)"
                        )
                        .padding(.bottom)
            
                        ForEach(0..<weatherViewModel.size, id: \.self) { index in
                            if let hourlyWeather = weatherViewModel.weatherData(at: index) {
                                VStack(alignment: .leading) {
                                    
                                    HourlyDataView(
                                        hourlyViewModel: HourlyWeatherViewModel(hourlyWeather: hourlyWeather),
                                        weatherViewModel: weatherViewModel
                                    )
                                }
                            }
                        }
                    } else {
                        Text("Loading weather data... (Or else search submit new data)")
                    }
                }

                InputView(
                    latitude: $latitude,
                    longitude: $longitude,
                    showError: $showError,
                    errorMessage: $errorMessage,
                    weatherViewModel: weatherViewModel
                )
                
            }
            .onAppear{
                self.weatherViewModel.fetchLatestWeatherData()
                print("Data \(self.weatherViewModel.weather.hourlyDataSize)")
            }
            .navigationTitle("Weather Foreact C API")
            .navigationBarTitleDisplayMode(.inline)
            .listStyle(GroupedListStyle())
        }
    }
}

struct HourlyDataView: View {
    let hourlyViewModel: HourlyWeatherViewModel
    var weatherViewModel: WeatherViewModel
    
    var body: some View {
        VStack(alignment: .leading) {
            let time = formatTimeString(hourlyViewModel.time)
            let icon = cloudIcon(hourlyViewModel.icon,isDayTime(time))
            
            Text("\(time)")
            
            HStack {
                Image("\(icon)")
                    .resizable()
                    .scaledToFit()
                    .frame(width: 60, height: 60)
                Text("\(hourlyViewModel.temperature) °C")
                
            }
        }
    }
}


struct InputView: View {
    @Binding var latitude: String
    @Binding var longitude: String
    @Binding var showError: Bool
    @Binding var errorMessage: String
    var weatherViewModel: WeatherViewModel
    
    var body: some View {
        HStack {
            TextField("Longitude", text: $longitude)
                .keyboardType(.decimalPad)
                .textFieldStyle(RoundedBorderTextFieldStyle())
                .padding()
            
            TextField("Latitude", text: $latitude)
                .keyboardType(.decimalPad)
                .textFieldStyle(RoundedBorderTextFieldStyle())
                .padding()
            
          
        }
        
        Button("Submit") {
            if latitude.isEmpty || longitude.isEmpty {
                showError = true
                errorMessage = "Please enter a value"
            } else if let lat = Double(latitude), let lon = Double(longitude) {
                weatherViewModel.fetchWeather(latitude: lat, longitude: lon) { result in
                    switch result {
                    case .success:
                        showError = false
                        errorMessage = ""
                        self.weatherViewModel.saveWeatherData()
                        self.weatherViewModel.printDatabaseContents()
                    case .failure:
                        showError = true
                        errorMessage = "Invalid location please try agian"
                    }
                }
            } else {
                showError = true
                errorMessage = "Please enter valid latitude and longitude values"
            }
            UIApplication.shared.sendAction(#selector(UIResponder.resignFirstResponder), to: nil, from: nil, for: nil)
            
        }
        
        
        if showError {
            Text(errorMessage)
                .foregroundColor(.red)
        }
    }
}


struct WeatherView_Previews: PreviewProvider {
    static var previews: some View {
        WeatherView()
            .environmentObject(DataController())

    }
}

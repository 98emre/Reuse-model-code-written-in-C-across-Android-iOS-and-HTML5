import Foundation

class WeatherViewModel: ObservableObject {
    @Published var errorMessage: String?
    @Published var showError: Bool = false

    @Published var weather: Weather
    private let dataController: DataController

    init(_ weather: Weather, _ dataController: DataController) {
           self.weather = weather
           self.dataController = dataController
    }
    
    var approvedTime: String {
        return weather.approvedTime
    }
    
    var latitude: Float {
        return weather.latitude
    }

    var longitude: Float {
        return weather.longitude
    }
    
    
    func appendWeatherData(hourlyData: HourlyWeather) {
        self.weather.appendHourlyData(hourlyData: hourlyData)
    }
    

    func weatherData(at index: Int) -> HourlyWeather? {
        return weather.hourlyData(at: index)
    }

    var size: Int {
        return weather.size
    }
    
    func updateLocation(latitude: Float, longitude: Float) {
        weather.latitude = latitude
        weather.longitude = longitude
    }
    
       
    func updateApprovedTime(approvedTime: String) {
        weather.approvedTime = approvedTime
    }
    
    func saveWeatherData() {
        dataController.saveWeatherData(weather)
    }

    func fetchLatestWeatherData() {
        if let weatherData = dataController.fetchWeatherData() {
            self.weather = weatherData
        }
    }
    
    
    func deleteAllData() {
        dataController.deleteAllData()
    }

    func printDatabaseContents() {
        dataController.printDatabaseContents()
    }
    
        
    func fetchWeather(latitude: Double, longitude: Double, completion: @escaping (Result<Void, Error>) -> Void){
        let weatherAPI = WeatherAPI()
        weatherAPI.fetchWeatherData(latitude: latitude, longitude: longitude) { result in
            DispatchQueue.main.async {
                switch result {
                case .success(let weather):
                    self.weather = weather
                    self.errorMessage = nil
                    self.showError = false
                    completion(.success(()))

                case .failure(let error):
                    print("Error fetching weather data: \(error)")
                    self.errorMessage = error.localizedDescription
                    self.showError = true
                    completion(.failure(error))

                }
            }
        }
    }

}








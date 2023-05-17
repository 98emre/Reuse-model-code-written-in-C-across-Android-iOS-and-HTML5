
import Foundation


// Weather View Model

class WeatherViewModel: ObservableObject {
    @Published var weather: WeatherData
    @Published var errorMessage: String?
    @Published var showError: Bool = false
    
    private let dataController: DataController


    init(weather: WeatherData, dataController: DataController) {
           self.weather = weather
           self.dataController = dataController
    }
    
    func appendHourlyWeather(hourlyWeather: HourlyWeatherData) {
        weather.getAllHourlyData.append(hourlyWeather)
    }

    func hourlyWeather(at index: Int) -> HourlyWeatherData? {
        if index < 0 || index >= weather.getAllHourlyData.count {
            return nil
        }
        return weather.getAllHourlyData[index]
    }

    var hourlyWeathersSize: Int {
        return weather.getAllHourlyData.count
    }

    func updateLocation(latitude: Double, longitude: Double) {
        weather.latitude = latitude
        weather.longitude = longitude
    }

    var latitude: Double {
        return weather.latitude
    }

    var longitude: Double {
        return weather.longitude
    }

    func updateApprovedTime(approvedTime: String) {
        weather.approvedTime = approvedTime
    }

    var approvedTime: String {
        return weather.approvedTime
    }

    func updateHourlyWeathers(hourlyWeathers: [HourlyWeatherData]) {
        weather.getAllHourlyData = hourlyWeathers
    }
        
    func saveWeatherData() {
        dataController.saveWeatherData(self.weather)
    }
    
    func deleteAllWeatherData() {
        dataController.deleteAllData()
    }
    
    func printDatabaseContents() {
        dataController.printDatabaseContents()
    }
    
    
    func fetchLatestWeatherData() {
        if let weatherData = dataController.fetchWeatherData() {
            self.weather = weatherData
        }
    }

    func fetchWeather(latitude: Double, longitude: Double, completion: @escaping (Result<Void, Error>) -> Void) {
        let weatherAPI = WeatherAPI()
        
        weatherAPI.fetchWeatherData(latitude: latitude, longitude: longitude){ result in
            switch result {
            case .success(let data):
                DispatchQueue.main.async {
                    self.weather.approvedTime = data.approvedTime
                    self.weather.getAllHourlyData = data.hourlyWeatherData.map { $0.hourlyWeather }
                    self.errorMessage = nil
                    self.showError = false
                    print("FEtchen: \(data.approvedTime)" )
                    completion(.success(()))
                }
            case .failure(let error):
                DispatchQueue.main.async {
                    self.errorMessage = error.localizedDescription
                    self.showError = true
                    completion(.failure(error))
                }
            }
        }
    }
    
}



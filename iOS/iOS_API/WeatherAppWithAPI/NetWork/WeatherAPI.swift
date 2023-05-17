

import Foundation
import CoreData

struct WeatherAPI {

    func fetchWeatherData(latitude: Double, longitude: Double, completion: @escaping (Result<(approvedTime: String, hourlyWeatherData: [HourlyWeatherViewModel]), Error>) -> Void) {
        let urlString = "https://opendata-download-metfcst.smhi.se/api/category/pmp3g/version/2/geotype/point/lon/\(longitude)/lat/\(latitude)/data.json"
       
        guard let url = URL(string: urlString) else {
            completion(.failure(NSError(domain: "", code: 0, userInfo: [NSLocalizedDescriptionKey: "Invalid URL"])))
            return
        }
        
        URLCache.shared.removeAllCachedResponses()

        let task = URLSession.shared.dataTask(with: url) { (data, response, error) in
            if let error = error {
                completion(.failure(error))
                return
            }
            guard let data = data else {
                let error = NSError(domain: "WeatherViewModel", code: 0, userInfo: [NSLocalizedDescriptionKey: "No data received"])
                completion(.failure(error))
                return
            }


            do {
                let decoder = JSONDecoder()
                let weatherApiResponse = try decoder.decode(WeatherApiResponse.self, from: data)
                print("Approved time: \(weatherApiResponse.approvedTime)")
                let approvedTime = weatherApiResponse.approvedTime
                let hourlyWeatherData = weatherApiResponse.timeSeries.map { weatherData -> HourlyWeatherViewModel in
                    let temperature = weatherData.parameters.first { $0.name == "t" }?.values.first ?? 0.0
                    let wsymb2 = weatherData.parameters.first { $0.name == "Wsymb2" }?.values.first ?? 0.0
                    let hourlyWeather = HourlyWeatherData(temperature: String(temperature), time: weatherData.validTime, icon: String(wsymb2))
                    return HourlyWeatherViewModel(hourlyWeather: hourlyWeather)
                }
                completion(.success((approvedTime, hourlyWeatherData)))
            } catch {
                completion(.failure(error))
            }
        }
        task.resume()

    }
}

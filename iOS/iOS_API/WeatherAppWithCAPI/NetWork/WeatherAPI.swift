import Foundation

struct WeatherAPI {
    
    func fetchWeatherData(latitude: Double, longitude: Double, completion: @escaping (Result<Weather, Error>) -> Void) {
        let urlString = "https://opendata-download-metfcst.smhi.se/api/category/pmp3g/version/2/geotype/point/lon/\(longitude)/lat/\(latitude)/data.json"
        guard let url = URL(string: urlString) else {
            let error = NSError(domain: "WeatherViewModel", code: 0, userInfo: [NSLocalizedDescriptionKey: "Invalid URL"])
            completion(.failure(error))
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
                let apiResponse = try JSONDecoder().decode(WeatherApiResponse.self, from: data)
                let weather = Weather(approvedTime: apiResponse.approvedTime,latitude: Float(latitude), longitude: Float(longitude))
                for timeSeries in apiResponse.timeSeries {
                    let time = timeSeries.validTime
                    let temperatureValues = timeSeries.parameters.filter { $0.name == "t" }.first?.values ?? []
                    let iconValues = timeSeries.parameters.filter { $0.name == "Wsymb2" }.first?.values ?? []
                    if let temperature = temperatureValues.first, let icon = iconValues.first {
                        let hourlyWeather = HourlyWeather(time: time, temperature: String(temperature), icon: String(icon))
                        weather.appendHourlyData(hourlyData: hourlyWeather)
                    }
                }
                completion(.success(weather))
            } catch {
                completion(.failure(error))
            }
        }
        task.resume()
    }
}


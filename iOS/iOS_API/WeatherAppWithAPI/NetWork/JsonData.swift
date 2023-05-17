
// Json Data

struct WeatherApiResponse: Decodable {
    let approvedTime: String
    let timeSeries: [TimeSeries]
}

struct TimeSeries: Decodable {
    let validTime: String
    let parameters: [Parameters]
}

struct Parameters: Decodable {
    let name: String
    let values: [Double]
}

import Foundation

class DummyData {
    static func getDummyViewModel() -> WeatherListViewModel {
        let dummyWeathers = [
            Weather(temperature: "-3", weekDay: "Mon", loadData: true, date: "1 Maj", prognosImage: "snowflake"),
            Weather(temperature: "18", weekDay: "Tis", loadData: true, date: "2 Maj", prognosImage: "cloud"),
            Weather(temperature: "22", weekDay: "Ons", loadData: true, date: "3 Maj", prognosImage: "sun.min"),
            Weather(temperature: "19", weekDay: "Tor", loadData: true, date: "4 Maj", prognosImage: "sun.min"),
            Weather(temperature: "16", weekDay: "Fre", loadData: true, date: "5 Maj", prognosImage: "sun.min")
        ]
        
        let dummyViewModel = WeatherListViewModel(weatherList: WeatherListData(cityName: "Stockholm", weathers: dummyWeathers))
        return dummyViewModel
    }
}

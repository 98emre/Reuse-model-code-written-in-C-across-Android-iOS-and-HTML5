import SwiftUI

struct WeatherView: View {
    @ObservedObject var viewModel: WeatherListViewModel = DummyData.getDummyViewModel()

    var body: some View {
        NavigationView {
            List {
                ForEach(0..<viewModel.size, id: \.self) { index in
                    if let weather = viewModel.weatherData(at: index) {
                        let weatherViewModel = WeatherViewModel(weather: weather)
                        HStack {
                            Image(systemName: weatherViewModel.prognosImage)
                                .resizable()
                                .aspectRatio(contentMode: .fit)
                                .frame(width: 30, height: 30)
                            
                            VStack{
                                Text(weatherViewModel.weekDay).font(.headline)
                                Text(weatherViewModel.date).font(.body)
                            }
                            .padding()
                            
                            Text("\(weatherViewModel.temperature)°")
                                .font(.title2)
                        }
                    }
                }
            }
            .navigationTitle(Text(viewModel.weatherList.cityName))
        }
    }
}

struct WeatherView_Previews: PreviewProvider {
    static var previews: some View {
        WeatherView()
    }
}

import SwiftUI

struct WeatherView: View {
    @ObservedObject var viewModel: WeatherListViewModel = DummyData.getDummyViewModel()

    var body: some View {
        NavigationView {
            List {
                ForEach(0..<viewModel.size, id: \.self) { index in
                    let weatherViewModel = WeatherViewModel(weather: viewModel.weatherData(at: index)!)
                    HStack {
                        Image(systemName: weatherViewModel.prognosImage)
                                                .resizable()
                                                .aspectRatio(contentMode: .fit)
                                                .frame(width: 40, height: 40)
                        
                        VStack{
                            Text(weatherViewModel.weekDay).font(.headline)
                            Text(weatherViewModel.date).font(.body)
                        }
                        .padding()
                        Text("\(weatherViewModel.temperature)°")
                            .font(.title2)
                            .fontWeight(.semibold)
                    }
                }
            }
            .navigationBarTitle(Text(viewModel.weatherList.cityName))
        }
    }
}

struct WeatherView_Previews: PreviewProvider {
    static var previews: some View {
        WeatherView()
    }
}

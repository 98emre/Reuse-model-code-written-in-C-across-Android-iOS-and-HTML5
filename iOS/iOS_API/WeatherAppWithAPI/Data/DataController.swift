
import Foundation
import CoreData

class DataController: ObservableObject {
        let container: NSPersistentContainer
    
        init() {
            container = NSPersistentContainer(name: "WeatherAppWithAPI")
            container.loadPersistentStores { (description, error) in
                if let error = error {
                       print("Core Data failed to load: \(error)")
                   }
            }
        }
    
    func saveWeatherData(_ weatherData: WeatherData) {
        let context = container.viewContext

        do {
            let locationID = "\(weatherData.latitude),\(weatherData.longitude)"

            let fetchRequest: NSFetchRequest<Weather> = Weather.fetchRequest()
            fetchRequest.predicate = NSPredicate(format: "locationID = %@", locationID)

            let existingWeathers = try context.fetch(fetchRequest)
            let weather: Weather

            if let existingWeather = existingWeathers.first {
                // If there is already a record with this locationID, update it
                weather = existingWeather
            } else {
                // If there is no record with this locationID, create a new one
                weather = Weather(context: context)
                weather.latitude = weatherData.latitude
                weather.longitude = weatherData.longitude
                weather.locationID = locationID
            }

            // Set merge policy to update existing values
            context.mergePolicy = NSMergeByPropertyObjectTrumpMergePolicy

            // Update (or set) the values for the Weather object
            weather.approvedTime = weatherData.approvedTime
            weather.timestamp = Date() // set the current date and time

            // Remove the old hourly weather data
            weather.removeFromHourlyWeathers(weather.hourlyWeathers ?? NSSet())

            for hourlyData in weatherData.getAllHourlyData {
                let hourlyWeather = HourlyWeather(context: context)
                hourlyWeather.temperature = hourlyData.temperature
                hourlyWeather.time = hourlyData.time
                hourlyWeather.icon = hourlyData.icon
                hourlyWeather.weather = weather  // associate the hourly weather with the weather
            }

            // Save the changes
            try context.save()

        } catch {
            print("Failed to fetch or save Weather: \(error)")
        }
    }



    func fetchWeatherData() -> WeatherData? {
        let context = container.viewContext

            // Skapa en hämtning för att hämta det senaste Weather-objektet
           let fetchRequest: NSFetchRequest<Weather> = Weather.fetchRequest()
           fetchRequest.sortDescriptors = [
               NSSortDescriptor(keyPath: \Weather.timestamp, ascending: false)
           ]
        do {
            // Utför hämtningen och konvertera resultatet till WeatherData
            if let weather = try context.fetch(fetchRequest).first {

                let hourlyFetchRequest: NSFetchRequest<HourlyWeather> = HourlyWeather.fetchRequest()
                hourlyFetchRequest.predicate = NSPredicate(format: "weather = %@", weather)
                hourlyFetchRequest.sortDescriptors = [NSSortDescriptor(keyPath: \HourlyWeather.time, ascending: true)]

                let hourlyWeathers = try context.fetch(hourlyFetchRequest)
                let weatherData = WeatherData(
                    weather.approvedTime ?? "",
                    hourlyWeathers.map { HourlyWeatherData(temperature: $0.temperature ?? "", time: $0.time ?? "",icon: $0.icon ?? "") },
                   weather.latitude,
                   weather.longitude
                )
                return weatherData
            }
        } catch {
            print("Failed to fetch Weather: \(error)")
        }

        return nil
    }


    
    

    
    func save(_ context: NSManagedObjectContext) {
        if context.hasChanges {
            do {
                try context.save()
                
                // Save the persistent store to a file for debugging purposes
                let storeURL = container.persistentStoreCoordinator.persistentStores.last?.url
                let fileManager = FileManager.default
                if let url = storeURL, let storeData = fileManager.contents(atPath: url.path) {
                    let documentsURL = fileManager.urls(for: .documentDirectory, in: .userDomainMask)[0]
                    let storeFileURL = documentsURL.appendingPathComponent("WeatherAppWithAPI.sqlite")
                    try storeData.write(to: storeFileURL)
                    print("Core Data store saved to file: \(storeFileURL)")
                }
                
            } catch {
                let nserror = error as NSError
                fatalError("Unresolved error \(nserror), \(nserror.userInfo)")
            }
        }
    }
    
    func deleteAllData() {
        let context = container.viewContext
        let fetchRequest: NSFetchRequest<NSFetchRequestResult> = NSFetchRequest(entityName: "Weather")
        let deleteRequest = NSBatchDeleteRequest(fetchRequest: fetchRequest)

        do {
            try context.execute(deleteRequest)
            try context.save()
        } catch let error as NSError {
            print("Could not delete. \(error), \(error.userInfo)")
        }
    }
    
    func printDatabaseContents() {
        let context = container.viewContext

        let fetchRequest: NSFetchRequest<Weather> = Weather.fetchRequest()

        do {
            let weathers = try context.fetch(fetchRequest)
            for weather in weathers {
                print("Location: \(weather.locationID ?? "")")
                print("Approved Time: \(weather.approvedTime ?? "")")
                print("Latitude: \(weather.latitude)")
                print("Longitude: \(weather.longitude)")

                print("---")
            }
        } catch {
            print("Failed to fetch Weather: \(error)")
        }
    }


    
}

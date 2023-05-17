

import Foundation
import CoreData

class DataController: ObservableObject {
    let container: NSPersistentContainer
    
    init() {
        container = NSPersistentContainer(name: "WeatherAppWithCAPI")
        container.loadPersistentStores { (description, error) in
            if let error = error {
                print("Core Data failed to load \(error)")
            }
        }
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
                    let storeFileURL = documentsURL.appendingPathComponent("WeatherAppWithCAPI.sqlite")
                    try storeData.write(to: storeFileURL)
                }
                
            } catch {
                let nserror = error as NSError
                fatalError("Unresolved error \(nserror), \(nserror.userInfo)")
            }
        }
    }
    func fetchWeatherData() -> Weather? {
        let context = container.viewContext

        // Create a fetch request to retrieve the latest WeatherEntity object
        let fetchRequest: NSFetchRequest<WeatherEntity> = WeatherEntity.fetchRequest()
        fetchRequest.sortDescriptors = [NSSortDescriptor(keyPath: \WeatherEntity.timestamp, ascending: false)]
        fetchRequest.fetchLimit = 1

        do {
            // Perform the fetch and convert the result to a Weather object
            if let weatherEntity = try context.fetch(fetchRequest).first {
                let latitude = Float(weatherEntity.latitude)
                let longitude = Float(weatherEntity.longitude)

                let hourlyFetchRequest: NSFetchRequest<HourlyWeatherEntity> = HourlyWeatherEntity.fetchRequest()
                hourlyFetchRequest.predicate = NSPredicate(format: "weather.latitude == %@ AND weather.longitude == %@", argumentArray: [latitude, longitude])
                hourlyFetchRequest.sortDescriptors = [NSSortDescriptor(keyPath: \HourlyWeatherEntity.time, ascending: true)]
                let hourlyWeatherEntities = try context.fetch(hourlyFetchRequest)

                var hourlyWeathers = [HourlyWeather]()
                for hourlyWeatherEntity in hourlyWeatherEntities {
                    let hourlyWeather = HourlyWeather(
                        time: hourlyWeatherEntity.time ?? "",
                        temperature: hourlyWeatherEntity.temperature ?? "",
                        icon: hourlyWeatherEntity.icon ?? ""
                    )
                    hourlyWeathers.append(hourlyWeather)
                }

                let weather = Weather(
                    approvedTime: weatherEntity.approvedTime ?? "",
                    latitude: latitude,
                    longitude: longitude
                )

                for hourlyWeather in hourlyWeathers {
                    weather.appendHourlyData(hourlyData: hourlyWeather)
                }

                return weather
            }
        } catch {
            print("Failed to fetch WeatherEntity: \(error)")
        }

        return nil
    }

   

    func saveWeatherData(_ weather: Weather) {
        let context = container.viewContext

        do {
            // Fetch existing WeatherEntity object for the current location
            let fetchRequest: NSFetchRequest<WeatherEntity> = WeatherEntity.fetchRequest()
            fetchRequest.predicate = NSPredicate(format: "latitude == %@ AND longitude == %@", argumentArray: [weather.latitude, weather.longitude])
            let existingWeatherEntities = try context.fetch(fetchRequest)

            if let existingWeatherEntity = existingWeatherEntities.first {
                // Update the existing WeatherEntity
                existingWeatherEntity.approvedTime = weather.approvedTime
                existingWeatherEntity.timestamp = Date() // Set the current timestamp


                // Remove all existing HourlyWeatherEntity objects for the current location
                if let hourlyWeatherEntities = existingWeatherEntity.hourlyWeathers {
                    existingWeatherEntity.removeFromHourlyWeathers(hourlyWeatherEntities)
                }
            } else {
                // Create a new WeatherEntity
                let weatherEntity = WeatherEntity(context: context)
                weatherEntity.approvedTime = weather.approvedTime
                weatherEntity.latitude = weather.latitude
                weatherEntity.longitude = weather.longitude
                weatherEntity.timestamp = Date() // Set the current timestamp
            }

            // Create and configure HourlyWeatherEntity objects for each piece of hourly data
            let weatherEntity = existingWeatherEntities.first ?? context.insertedObjects.compactMap { $0 as? WeatherEntity }.first
            let hourlyWeatherSet = weatherEntity?.mutableSetValue(forKey: "hourlyWeathers")
            for i in 0..<weather.hourlyDataSize {
                if let hourlyWeather = weather.hourlyData(at: i) {
                    let hourlyWeatherEntity = HourlyWeatherEntity(context: context)
                    hourlyWeatherEntity.time = hourlyWeather.time
                    hourlyWeatherEntity.temperature = hourlyWeather.temperature
                    hourlyWeatherEntity.icon = hourlyWeather.icon
                    hourlyWeatherSet?.add(hourlyWeatherEntity)
                }
            }

            // Save the changes
            save(context)
        } catch {
            print("Failed to save weather data: \(error)")
        }
    }

    
    
    
    
    
    func deleteAllData() {
        let context = container.viewContext
        let fetchRequest: NSFetchRequest<NSFetchRequestResult> = NSFetchRequest(entityName: "WeatherEntity")
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

        let fetchRequest: NSFetchRequest<WeatherEntity> = WeatherEntity.fetchRequest()

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

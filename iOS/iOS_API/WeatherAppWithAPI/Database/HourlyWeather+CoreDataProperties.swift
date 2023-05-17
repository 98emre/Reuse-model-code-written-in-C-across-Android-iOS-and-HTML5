


import Foundation
import CoreData


extension HourlyWeather {

    @nonobjc public class func fetchRequest() -> NSFetchRequest<HourlyWeather> {
        return NSFetchRequest<HourlyWeather>(entityName: "HourlyWeather")
    }

    @NSManaged public var icon: String?
    @NSManaged public var id: UUID?
    @NSManaged public var temperature: String?
    @NSManaged public var time: String?
    @NSManaged public var weather: Weather?

}

extension HourlyWeather : Identifiable {

}

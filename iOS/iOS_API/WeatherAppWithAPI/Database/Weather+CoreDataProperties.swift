

import Foundation
import CoreData


extension Weather {

    @nonobjc public class func fetchRequest() -> NSFetchRequest<Weather> {
        return NSFetchRequest<Weather>(entityName: "Weather")
    }

    @NSManaged public var approvedTime: String?
    @NSManaged public var id: UUID?
    @NSManaged public var latitude: Double
    @NSManaged public var longitude: Double
    @NSManaged public var timestamp: Date?
    @NSManaged public var locationID: String?
    @NSManaged public var hourlyWeathers: NSSet?

}

// MARK: Generated accessors for hourlyWeathers
extension Weather {

    @objc(addHourlyWeathersObject:)
    @NSManaged public func addToHourlyWeathers(_ value: HourlyWeather)

    @objc(removeHourlyWeathersObject:)
    @NSManaged public func removeFromHourlyWeathers(_ value: HourlyWeather)

    @objc(addHourlyWeathers:)
    @NSManaged public func addToHourlyWeathers(_ values: NSSet)

    @objc(removeHourlyWeathers:)
    @NSManaged public func removeFromHourlyWeathers(_ values: NSSet)

}

extension Weather : Identifiable {

}

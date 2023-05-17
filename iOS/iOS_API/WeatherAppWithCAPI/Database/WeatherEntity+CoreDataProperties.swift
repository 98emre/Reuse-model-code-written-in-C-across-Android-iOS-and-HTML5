//
//  WeatherEntity+CoreDataProperties.swift
//  WeatherAppWithCAPI
//
//  Created by Mateusz Al Halabi on 2023-05-13.
//
//

import Foundation
import CoreData


extension WeatherEntity {

    @nonobjc public class func fetchRequest() -> NSFetchRequest<WeatherEntity> {
        return NSFetchRequest<WeatherEntity>(entityName: "WeatherEntity")
    }

    @NSManaged public var approvedTime: String?
    @NSManaged public var id: UUID?
    @NSManaged public var latitude: Float
    @NSManaged public var longitude: Float
    @NSManaged public var locationID: String?
    @NSManaged public var timestamp: Date?
    @NSManaged public var hourlyWeathers: NSSet?

}

// MARK: Generated accessors for hourlyWeathers
extension WeatherEntity {

    @objc(addHourlyWeathersObject:)
    @NSManaged public func addToHourlyWeathers(_ value: HourlyWeatherEntity)

    @objc(removeHourlyWeathersObject:)
    @NSManaged public func removeFromHourlyWeathers(_ value: HourlyWeatherEntity)

    @objc(addHourlyWeathers:)
    @NSManaged public func addToHourlyWeathers(_ values: NSSet)

    @objc(removeHourlyWeathers:)
    @NSManaged public func removeFromHourlyWeathers(_ values: NSSet)

}

extension WeatherEntity : Identifiable {

}

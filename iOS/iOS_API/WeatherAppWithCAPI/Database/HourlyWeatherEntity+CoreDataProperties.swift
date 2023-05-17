//
//  HourlyWeatherEntity+CoreDataProperties.swift
//  WeatherAppWithCAPI
//
//  Created by Mateusz Al Halabi on 2023-05-13.
//
//

import Foundation
import CoreData


extension HourlyWeatherEntity {

    @nonobjc public class func fetchRequest() -> NSFetchRequest<HourlyWeatherEntity> {
        return NSFetchRequest<HourlyWeatherEntity>(entityName: "HourlyWeatherEntity")
    }

    @NSManaged public var icon: String?
    @NSManaged public var id: UUID?
    @NSManaged public var temperature: String?
    @NSManaged public var time: String?
    @NSManaged public var weather: WeatherEntity?

}

extension HourlyWeatherEntity : Identifiable {

}

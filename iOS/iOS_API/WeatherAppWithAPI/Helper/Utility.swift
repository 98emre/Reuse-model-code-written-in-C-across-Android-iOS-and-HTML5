

import Foundation

// Helpers Funktioner


func formatTimeString(_ timeString: String) -> String {
    let dateFormatter = DateFormatter()
    dateFormatter.dateFormat = "yyyy-MM-dd'T'HH:mm:ss'Z'"
    dateFormatter.timeZone = TimeZone(identifier: "UTC") // Ange UTC tidszon
    
    if let utcDate = dateFormatter.date(from: timeString) {
        dateFormatter.timeZone = TimeZone(identifier: "Europe/Paris") // Ange CEST tidszon
        dateFormatter.dateFormat = "yyyy-MM-dd HH:mm"
        let cestString = dateFormatter.string(from: utcDate)
        return cestString
    } else {
        return timeString
    }
}

func cloudIcon(_ value: String, _ isDayTime: Bool) -> String {
    switch value {
    case "1.0":
        return isDayTime ? "day1" : "night1"
    case "2.0":
        return isDayTime ? "day2" : "night2"
    case "3.0":
        return isDayTime ? "day3" : "night3"
    case "4.0":
        return isDayTime ? "day4" : "night4"
    case "5.0":
        return isDayTime ? "day5" : "night5"
    case "6.0":
        return isDayTime ? "day6" : "night6"
    case "7.0":
        return isDayTime ? "day7" : "night7"
    case "8.0":
        return isDayTime ? "day8" : "night8"
    case "9.0":
        return isDayTime ? "day9" : "night9"
    case "10.0":
        return isDayTime ? "day10" : "night10"
    case "11.0":
        return isDayTime ? "day11" : "night11"
    case "12.0":
        return isDayTime ? "day12" : "night12"
    case "13.0":
        return isDayTime ? "day13" : "night13"
    case "14.0":
        return isDayTime ? "day14" : "night14"
    case "15.0":
        return isDayTime ? "day15" : "night15"
    case "16.0":
        return isDayTime ? "day16" : "night16"
    case "17.0":
        return isDayTime ? "day17" : "night17"
    case "18.0":
        return isDayTime ? "day18" : "night18"
    case "19.0":
        return isDayTime ? "day19" : "night19"
    case "20.0":
        return isDayTime ? "day20" : "night20"
    case "21.0":
        return isDayTime ? "day21" : "night21"
    case "22.0":
        return isDayTime ? "day22" : "night22"
    case "23.0":
        return isDayTime ? "day23" : "night23"
    case "24.0":
        return isDayTime ? "day24" : "night24"
    case "25.0":
        return isDayTime ? "day25" : "night25"
    case "26.0":
        return isDayTime ? "day26" : "night26"
    case "27.0":
        return isDayTime ? "day27" : "night27"
    default:
        return "Unknown cloud coverage"
    }
}

func isDayTime(_ timeString: String) -> Bool {
    let dateFormatter = DateFormatter()
    dateFormatter.dateFormat = "yyyy-MM-dd HH:mm"
    dateFormatter.timeZone = TimeZone(secondsFromGMT: 0)
    
    if let date = dateFormatter.date(from: timeString) {
        let calendar = Calendar.current
        let hour = calendar.component(.hour, from: date)
                
        return hour >= 6 && hour <= 22
    } else {
        return false
    }
}

/*
 func formatTimeString(_ timeString: String) -> String {
     let dateFormatter = DateFormatter()
     dateFormatter.dateFormat = "yyyy-MM-dd'T'HH:mm:ss'Z'"
     
     if let date = dateFormatter.date(from: timeString) {
         dateFormatter.dateFormat = "yyyy-MM-dd HH:mm"
         return dateFormatter.string(from: date)
     } else {
         return timeString
     }
 }

 */

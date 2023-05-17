package com.example.weatherappcapi.utils

import java.text.SimpleDateFormat
import java.time.ZoneId
import java.time.ZoneOffset
import java.time.ZonedDateTime
import java.time.format.DateTimeFormatter
import java.util.*

/*fun formatDateTime(dateTimeStr: String): String {
    val dateFormat = SimpleDateFormat("yyyy-MM-dd'T'HH:mm:ss'Z'", Locale.getDefault())
    val date = dateFormat.parse(dateTimeStr)
    val formattedDateFormat = SimpleDateFormat("yyyy-MM-dd HH:mm", Locale.getDefault())
    return formattedDateFormat.format(date!!)
} */

fun formatDateTime(dateTimeStr: String): String {
    val formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd'T'HH:mm:ss'Z'")
    val utcDateTime = ZonedDateTime.parse(dateTimeStr, formatter.withZone(ZoneOffset.UTC))
    val cestDateTime = utcDateTime.withZoneSameInstant(ZoneId.systemDefault())
    return cestDateTime.format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm"))
}

fun getWeatherSymbolDrawableName(weatherSymbol: String, isDay: Boolean): String {
    return when (weatherSymbol) {
        "1" -> if (isDay) "day1" else "night1"
        "2" -> if (isDay) "day2" else "night2"
        "3" -> if (isDay) "day3" else "night3"
        "4" -> if (isDay) "day4" else "night4"
        "5" -> if (isDay) "day5" else "night5"
        "6" -> if (isDay) "day6" else "night6"
        "7" -> if (isDay) "day7" else "night7"
        "8" -> if (isDay) "day8" else "night8"
        "9" -> if (isDay) "day9" else "night9"
        "10" -> if (isDay) "day10" else "night10"
        "11" -> if (isDay) "day11" else "night11"
        "12" -> if (isDay) "day12" else "night12"
        "13" -> if (isDay) "day13" else "night13"
        "14" -> if (isDay) "day14" else "night14"
        "15" -> if (isDay) "day15" else "night15"
        "16" -> if (isDay) "day16" else "night16"
        "17" -> if (isDay) "day17" else "night17"
        "18" -> if (isDay) "day18" else "night18"
        "19" -> if (isDay) "day19" else "night19"
        "20" -> if (isDay) "day20" else "night20"
        "21" -> if (isDay) "day21" else "night21"
        "22" -> if (isDay) "day22" else "night22"
        "23" -> if (isDay) "day23" else "night23"
        "24" -> if (isDay) "day24" else "night24"
        "25" -> if (isDay) "day25" else "night25"
        "26" -> if (isDay) "day26" else "night26"
        "27" -> if (isDay) "day27" else "night27"
        else -> ""
    }
}

fun isDayTime(validTime: String): Boolean {
    val dateFormat = SimpleDateFormat("yyyy-MM-dd HH:mm", Locale.getDefault())
    val date = dateFormat.parse(validTime)
    val hour = date?.hours ?: return false
    return hour >= 4 && hour <= 20
}
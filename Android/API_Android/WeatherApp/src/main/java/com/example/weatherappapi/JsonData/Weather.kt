package com.example.weatherappapi.JsonData

data class Weather(
    val approvedTime: String,
    val geometry: Geometry,
    val referenceTime: String,
    val timeSeries: List<TimeSery>
)
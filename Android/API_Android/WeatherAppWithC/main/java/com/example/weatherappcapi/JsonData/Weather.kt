package com.example.weatherappcapi.JsonData

data class Weather(
    val approvedTime: String,
    val geometry: Geometry,
    val referenceTime: String,
    val timeSeries: List<TimeSerie>
)
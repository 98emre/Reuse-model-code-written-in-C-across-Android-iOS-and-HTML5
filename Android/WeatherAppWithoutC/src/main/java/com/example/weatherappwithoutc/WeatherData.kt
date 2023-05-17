package com.example.weatherappwithoutc


data class WeatherData(
    var approvedTime: String,
    private val _data: MutableList<HourlyWeatherData> = mutableListOf(),
    private var _size: Int = 0,
    var lat: Double = 0.0,
    var lon: Double = 0.0
) {
    data class HourlyWeatherData(
        var time: String,
        var temperature: String,
        var icon: String
    )

    val data: List<HourlyWeatherData>
        get() = _data

    var size: Int
        get() = _size
        set(value) {
            _size = value
        }

    fun addHourlyData(hourlyData: HourlyWeatherData) {
        _data.add(hourlyData)
        _size++
    }
}



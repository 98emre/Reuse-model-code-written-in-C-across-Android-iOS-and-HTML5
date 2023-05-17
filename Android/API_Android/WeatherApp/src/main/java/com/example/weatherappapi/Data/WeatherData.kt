package com.example.weatherappapi.Data


data class WeatherData(
    var approvedTime: String,
    private val _data: MutableList<HourlyWeatherData> = mutableListOf(),
    private var _size: Int = 0,
    var lat: Float = 0F,
    var lon: Float = 0F
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



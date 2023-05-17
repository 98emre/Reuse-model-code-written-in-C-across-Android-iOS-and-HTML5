package com.example.weatherapp

class WeatherNative {

    data class HourlyWeatherData(
        var time: String,
        var temperature: String,
        var icon: String
    )

    private var approvedTime: String = ""
    private var size: Int = 0
    private var data: MutableList<HourlyWeatherData> = mutableListOf()
    private var lat: Float = 0F
    private var lon: Float = 0F

    companion object {
        init {
            System.loadLibrary("JniBridge")
        }
    }

    external fun createWeatherObjectFromC(approvedTime: String): WeatherNative
    external fun getApprovedTime(data: WeatherNative): String
    external fun setApprovedTime(data: WeatherNative, approvedTime: String)
    external fun getLat(data: WeatherNative): Double
    external fun setLat(data: WeatherNative, lat: Double)
    external fun getLon(data: WeatherNative): Double
    external fun setLon(data: WeatherNative, lon: Double)

    external fun createHourlyWeatherObjectFromC(time: String, temperature: String, icon: String): HourlyWeatherData
    external fun getTime(data: HourlyWeatherData): String
    external fun setTime(data: HourlyWeatherData, time: String)
    external fun getTemperature(data: HourlyWeatherData): String
    external fun setTemperature(data: HourlyWeatherData, temperature: String)
    external fun getIcon(data: HourlyWeatherData): String
    external fun setIcon(data: HourlyWeatherData, icon: String)

    external fun getHourlyData(data: WeatherNative, index: Int): HourlyWeatherData
    external fun addHourlyData(data: WeatherNative, hourlyData: HourlyWeatherData)
    external fun getHourlyDataSize(data: WeatherNative): Int

}

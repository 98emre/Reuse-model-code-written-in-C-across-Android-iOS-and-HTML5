package com.example.weatherappwithoutc

class DummyData(private val weather: WeatherData) {

    fun getAllDummyData(): List<WeatherData.HourlyWeatherData> {
        val hourlyDataList = mutableListOf<WeatherData.HourlyWeatherData>()
        for (i in 0 until 100) {
            hourlyDataList.add(WeatherData.HourlyWeatherData("2022-05-15 18:00 ", "10 C", "1"))
        }
        return hourlyDataList
    }
}


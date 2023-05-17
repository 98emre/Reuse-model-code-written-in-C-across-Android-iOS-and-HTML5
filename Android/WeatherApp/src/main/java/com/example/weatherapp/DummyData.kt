package com.example.weatherapp

class DummyData(private val weatherNative: WeatherNative) {

    fun getAllDummyData(data: WeatherNative) {

        for (i in 0 until 100) {
            data.addHourlyData(data,weatherNative.createHourlyWeatherObjectFromC("2022-05-01 00:00","3", "sunny"))
        }
    }

}
 // 100 - 635 041
// 1000 - 7 882 042
// 10000 - 64 100 167
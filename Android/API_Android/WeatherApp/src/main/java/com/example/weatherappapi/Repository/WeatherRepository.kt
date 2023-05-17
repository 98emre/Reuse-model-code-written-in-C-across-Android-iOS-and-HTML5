package com.example.weatherappapi.Repository

import android.util.Log
import com.example.weatherappapi.Data.*
import com.example.weatherappapi.Network.WeatherAPI
import com.example.weatherappapi.Room.WeatherDao
import com.example.weatherappapi.utils.formatDateTime
import java.util.*
import javax.inject.Inject

class WeatherRepository @Inject constructor(
    private val api: WeatherAPI,
    private val weatherDataDao: WeatherDao
    ) {
    suspend fun getWeatherData(lon: Double, lat: Double): WeatherData? {
        try {
            val weather = api.getWeather(lon, lat)
            val weatherData = WeatherData(
                approvedTime = formatDateTime(weather.approvedTime),
                lat = lat.toFloat(),
                lon = lon.toFloat()
            )

            val hourlyData = weather.timeSeries.mapNotNull {
                val time = formatDateTime(it.validTime)
                val temperature = it.parameters.find { p -> p.name == "t" }?.values?.get(0)?.toString() ?: ""
                val icon = it.parameters.find { p -> p.name == "Wsymb2" }?.values?.get(0)?.toInt()?.toString() ?: ""

                WeatherData.HourlyWeatherData(
                    time = time,
                    temperature = temperature,
                    icon = icon
                )
            }

            hourlyData.forEach { data ->
                weatherData.addHourlyData(data)
            }
            saveWeatherData(weatherData)

            return weatherData
        } catch (e: Exception) {
            Log.e("WeatherRepository", "Error getting weather data", e)
            return null
        }
    }

    private suspend fun saveWeatherData(weatherData: WeatherData) {
        val existingWeatherData = weatherDataDao.getWeatherDataByLocation(weatherData.lat.toDouble(), weatherData.lon.toDouble())

        if (existingWeatherData != null) {
            existingWeatherData.approvedTime = weatherData.approvedTime
            existingWeatherData.timeStamp = Date()

            weatherDataDao.deleteHourlyDataByWeatherId(existingWeatherData.id)

            val hourlyWeatherEntities = weatherData.data.map { hourlyData ->
                HourlyWeatherDataEntity(
                    time = hourlyData.time,
                    temperature = hourlyData.temperature,
                    icon = hourlyData.icon,
                    weatherDataId = existingWeatherData.id
                )
            }

            val weatherWithHourlyData = WeatherWithHourlyData(existingWeatherData, hourlyWeatherEntities)

            weatherDataDao.updateWeather(existingWeatherData)
            weatherDataDao.saveHourlyData(weatherWithHourlyData)
        }

        else {
            val weatherEntity = WeatherDataEntity(
                approvedTime = weatherData.approvedTime,
                lat = weatherData.lat,
                lon = weatherData.lon,
                timeStamp = Date(),
                locationID = "${weatherData.lon}, ${weatherData.lat}"
            )

            val weatherDataId = weatherDataDao.insertWeather(weatherEntity)

            val hourlyWeatherEntities = weatherData.data.map { hourlyData ->
                HourlyWeatherDataEntity(
                    weatherDataId = weatherDataId.toInt(),
                    time = hourlyData.time,
                    temperature = hourlyData.temperature,
                    icon = hourlyData.icon
                )
            }
            val weatherWithHourlyData = WeatherWithHourlyData(weatherEntity, hourlyWeatherEntities)

            weatherDataDao.saveHourlyData(weatherWithHourlyData)
        }
    }

    suspend fun printDatabaseContents() {
        val allWeather = weatherDataDao.getWeatherWithHourlyData()

        allWeather.forEach { weatherWithHourlyData ->
            val weather = weatherWithHourlyData.weather
            val hourly = weatherWithHourlyData.hourlyData
            println("\nLocation: ${weather.locationID}")
            println("Approved Time: ${weather.approvedTime}")
            println("Latitude: ${weather.lat}")
            println("Longitude: ${weather.lon}")
           /* hourly.forEach {
                println("Time: ${it.time}")
                println("Temp: ${it.temperature}")
                println("Icon: ${it.icon}")
            } */
            println("\n===================================\n")
        }
    }

    suspend fun getSavedWeatherData(): WeatherData? {
        val weatherWithHourlyData = weatherDataDao.getLatestWeatherData()

        return weatherWithHourlyData?.let { weather ->
            WeatherData(
                approvedTime = weather.weather.approvedTime,
                lat = weather.weather.lat,
                lon = weather.weather.lon
            ).apply {
                weather.hourlyData.forEach { hourlyWeatherData ->
                    addHourlyData(
                        WeatherData.HourlyWeatherData(
                            time = hourlyWeatherData.time,
                            temperature = hourlyWeatherData.temperature,
                            icon = hourlyWeatherData.icon
                        )
                    )
                }
            }
        }
    }
}













package com.example.weatherappcapi.Repository

import android.util.Log
import com.example.weatherappcapi.Network.WeatherAPI
import com.example.weatherappcapi.Room.HourlyWeatherDataEntity
import com.example.weatherappcapi.Room.WeatherDao
import com.example.weatherappcapi.Room.WeatherDataEntity
import com.example.weatherappcapi.Room.WeatherWithHourlyData
import com.example.weatherappcapi.WeatherNative
import com.example.weatherappcapi.utils.formatDateTime
import java.util.*

class WeatherRepository(
    private val api: WeatherAPI,
    private val weatherDataDao: WeatherDao)
{
    suspend fun getWeather(lon: Double, lat: Double): WeatherNative {
        val weather = api.getWeather(lon, lat)
        val approvedTime = formatDateTime(weather.approvedTime)
        val weatherNative = WeatherNative().createWeatherObjectFromC(approvedTime)
        weatherNative.setLon(weatherNative,lon)
        weatherNative.setLat(weatherNative,lat)


        val hourlyData = weather.timeSeries.map {
            val time = formatDateTime(it.validTime)
            val temperature = it.parameters.find { p -> p.name == "t" }?.values?.get(0)?.toString() ?: ""
            val icon = it.parameters.find { p -> p.name == "Wsymb2" }?.values?.get(0)?.toInt()?.toString() ?: ""

            WeatherNative().createHourlyWeatherObjectFromC(time, temperature, icon)
        }
        hourlyData.forEach { data ->
            WeatherNative().addHourlyData(weatherNative, data)
        }

        saveWeatherData(weatherNative)

        return weatherNative
    }

    private suspend fun saveWeatherData(weatherData: WeatherNative) {

        val lat = weatherData.getLat(weatherData)
        val lon = weatherData.getLon(weatherData)

        val existingWeatherData = weatherDataDao.getWeatherDataByLocation(lat, lon)

        if (existingWeatherData != null){
            existingWeatherData.approvedTime = weatherData.getApprovedTime(weatherData)
            existingWeatherData.timeStamp = Date()

            weatherDataDao.deleteHourlyDataByWeatherId(existingWeatherData.id)

            val hourlyWeatherSize = weatherData.getHourlyDataSize(weatherData)
            val hourlyWeatherEntities = mutableListOf<HourlyWeatherDataEntity>()

            for (i in 0 until hourlyWeatherSize) {
                val hourlyData = weatherData.getHourlyData(weatherData, i)
                hourlyWeatherEntities.add(
                    HourlyWeatherDataEntity(
                        time = weatherData.getTime(hourlyData),
                        temperature = weatherData.getTemperature(hourlyData),
                        icon = weatherData.getIcon(hourlyData),
                        weatherDataId = existingWeatherData.id // Använder Generead Id här
                    )
                )
            }

            val weatherWithHourlyData = WeatherWithHourlyData(existingWeatherData, hourlyWeatherEntities)

            weatherDataDao.updateWeather(existingWeatherData)
            weatherDataDao.saveHourlyData(weatherWithHourlyData)

        }

        else {
            val weatherEntity = WeatherDataEntity(
                approvedTime = weatherData.getApprovedTime(weatherData),
                lat = weatherData.getLat(weatherData).toFloat(),
                lon = weatherData.getLon(weatherData).toFloat(),
                timeStamp = Date(),
                locationID = "${lon.toFloat()}, ${lat.toFloat()}")

            // Insert  WeatherDataEntity till databasen och hämtar  generad ID
            val weatherDataId = weatherDataDao.insertWeather(weatherEntity)

            val hourlyWeatherSize = weatherData.getHourlyDataSize(weatherData)
            val hourlyWeatherEntities = mutableListOf<HourlyWeatherDataEntity>()

            for (i in 0 until hourlyWeatherSize) {
                val hourlyData = weatherData.getHourlyData(weatherData, i)
                hourlyWeatherEntities.add(
                    HourlyWeatherDataEntity(
                        time = weatherData.getTime(hourlyData),
                        temperature = weatherData.getTemperature(hourlyData),
                        icon = weatherData.getIcon(hourlyData),
                        weatherDataId = weatherDataId.toInt() // Använder Generead Id här
                    )
                )
            }

            /* Insert alla HourlyWeatherDataEntity till databasen
            hourlyWeatherEntities.forEach {
                weatherDataDao.insertHourlyWeather(it)
            } */

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


    suspend fun getLatestWeatherData(): WeatherNative? {
        val weatherWithHourlyData = weatherDataDao.getLatestWeatherData()

        if (weatherWithHourlyData != null) {
            val weatherNative = WeatherNative().createWeatherObjectFromC(weatherWithHourlyData.weather.approvedTime)
            weatherNative.setLon(weatherNative, weatherWithHourlyData.weather.lon.toDouble())
            weatherNative.setLat(weatherNative,weatherWithHourlyData.weather.lat.toDouble())

            weatherWithHourlyData.hourlyData.forEach { data ->
                val hourlyWeatherData = weatherNative.createHourlyWeatherObjectFromC(data.time, data.temperature, data.icon)
                weatherNative.addHourlyData(weatherNative, hourlyWeatherData)
            }
            return weatherNative
        }

        else {
            Log.i("WeatherRepository", "No data in database.")
            return null
        }
    }
}


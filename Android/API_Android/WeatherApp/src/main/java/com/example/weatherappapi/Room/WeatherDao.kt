package com.example.weatherappapi.Room

import androidx.room.*
import com.example.weatherappapi.Data.HourlyWeatherDataEntity
import com.example.weatherappapi.Data.WeatherDataEntity
import com.example.weatherappapi.Data.WeatherWithHourlyData

@Dao
interface WeatherDao {

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun insertWeather(weather: WeatherDataEntity): Long

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun insertHourlyWeather(hourlyWeather: HourlyWeatherDataEntity)

    @Update
    suspend fun updateWeather(weather: WeatherDataEntity)
    
    @Query("SELECT * FROM weather_data WHERE lat = :lat AND lon = :lon")
    suspend fun getWeatherDataByLocation(lat: Double, lon: Double): WeatherDataEntity?

    @Query("DELETE FROM HourlyWeatherDataEntity WHERE weatherDataId = :weatherDataId")
    suspend fun deleteHourlyDataByWeatherId(weatherDataId: Int)

    @Transaction
    @Query("SELECT * FROM weather_data")
    suspend fun getWeatherWithHourlyData(): List<WeatherWithHourlyData>

    @Query("SELECT * FROM weather_data ORDER BY timeStamp DESC LIMIT 1")
    suspend fun getLatestWeatherData(): WeatherWithHourlyData?


    @Transaction
    suspend fun saveHourlyData(weatherWithHourlyData: WeatherWithHourlyData) {
        for (hourlyData in weatherWithHourlyData.hourlyData) {
            insertHourlyWeather(hourlyData)
        }
    }
}


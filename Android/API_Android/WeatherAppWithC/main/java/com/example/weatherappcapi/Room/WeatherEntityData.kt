package com.example.weatherappcapi.Room

import androidx.room.Embedded
import androidx.room.Entity
import androidx.room.PrimaryKey
import androidx.room.Relation
import java.util.Date

@Entity(tableName = "weather_data")
data class WeatherDataEntity(
    @PrimaryKey(autoGenerate = true)
    val id: Int = 0,
    var approvedTime: String,
    val lat: Float,
    val lon: Float,
    var timeStamp: Date,
    val locationID: String
)

@Entity
data class HourlyWeatherDataEntity(
    @PrimaryKey(autoGenerate = true)
    val id: Int = 0,
    var weatherDataId: Int,
    val time: String,
    val temperature: String,
    val icon: String,
)

data class WeatherWithHourlyData(
    @Embedded val weather: WeatherDataEntity,
    @Relation(
        parentColumn = "id",
        entityColumn = "weatherDataId"
    )
    val hourlyData: List<HourlyWeatherDataEntity>
)


package com.example.weatherappcapi.Network

import android.content.Context
import androidx.room.Room
import com.example.weatherappcapi.Repository.WeatherRepository
import com.example.weatherappcapi.Room.WeatherDao
import com.example.weatherappcapi.Room.WeatherDatabase
import dagger.Module
import dagger.Provides
import dagger.hilt.InstallIn
import dagger.hilt.android.qualifiers.ApplicationContext
import dagger.hilt.components.SingletonComponent
import retrofit2.Retrofit
import retrofit2.converter.gson.GsonConverterFactory
import javax.inject.Singleton

@Module
@InstallIn(SingletonComponent::class)
object WeatherModule {

    @Provides
    @Singleton
    fun provideWeatherAPI(): WeatherAPI {
        return Retrofit.Builder()
            .baseUrl("https://opendata-download-metfcst.smhi.se/api/")
            .addConverterFactory(GsonConverterFactory.create())
            .build()
            .create(WeatherAPI::class.java)
    }

    @Provides
    @Singleton
    fun provideWeatherRepository(weatherAPI: WeatherAPI,weatherDataDao: WeatherDao): WeatherRepository {
        return WeatherRepository(weatherAPI,weatherDataDao)
    }

    @Provides
    @Singleton
    fun provideWeatherDatabase(@ApplicationContext context: Context): WeatherDatabase {
        return Room.databaseBuilder(
            context.applicationContext,
            WeatherDatabase::class.java,
            "weather_database")
            .fallbackToDestructiveMigration()
            .build()
    }

    @Provides
    fun provideWeatherDataDao(weatherDatabase: WeatherDatabase): WeatherDao {
        return weatherDatabase.weatherDataDao()
    }
}
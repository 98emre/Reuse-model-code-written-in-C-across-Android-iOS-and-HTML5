package com.example.weatherappcapi.Model

import android.util.Log
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import com.example.weatherappcapi.Repository.WeatherRepository
import com.example.weatherappcapi.WeatherNative
import dagger.hilt.android.lifecycle.HiltViewModel
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.launch
import javax.inject.Inject

@HiltViewModel
class WeatherViewModel @Inject constructor(private val weatherRepository: WeatherRepository) : ViewModel() {

    val weatherData: MutableStateFlow<WeatherNative?> = MutableStateFlow(null)
    val weatherDataSize: MutableStateFlow<Int?> = MutableStateFlow(null)

    private val _error: MutableStateFlow<Boolean> = MutableStateFlow(false)
    val error: StateFlow<Boolean> = _error

    private val _errorDatabase: MutableStateFlow<Boolean> = MutableStateFlow(false)
    val errorDatabase: StateFlow<Boolean> = _errorDatabase

    fun getWeather(lon: Double, lat: Double) {
        viewModelScope.launch(Dispatchers.IO) {
            try {
                val weatherNative = weatherRepository.getWeather(lon, lat)
                weatherDataSize.value = WeatherNative().getHourlyDataSize(weatherNative)
                weatherData.value = weatherNative
                _error.value = false
                _errorDatabase.value = false
            } catch (e: Exception) {
                Log.e("WeatherViewModel", "Error getting weather data", e)
                _error.value = true
            }
        }
    }

    fun printAllData() {
        viewModelScope.launch(Dispatchers.IO) {
            weatherRepository.printDatabaseContents()
        }
    }

    fun getSavedWeatherData() {
        viewModelScope.launch(Dispatchers.IO) {
            val savedWeatherData = weatherRepository.getLatestWeatherData()

            if (savedWeatherData != null) {
                weatherData.value = savedWeatherData
                weatherDataSize.value = WeatherNative().getHourlyDataSize(savedWeatherData)
                _errorDatabase.value = false
            } else {
                Log.e("WeatherViewModel", "No saved weather data found")
                _errorDatabase.value = true
            }
        }
    }
}




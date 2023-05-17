package com.example.weatherappapi.Model

import android.util.Log
import androidx.compose.runtime.mutableStateOf
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import com.example.weatherappapi.Data.WeatherData
import com.example.weatherappapi.Repository.WeatherRepository
import dagger.hilt.android.lifecycle.HiltViewModel
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.launch
import javax.inject.Inject

@HiltViewModel
class WeatherViewModel @Inject constructor(private val weatherRepository: WeatherRepository) : ViewModel() {

    val _weatherData: MutableStateFlow<WeatherData?> = MutableStateFlow(null)
    private val _error: MutableStateFlow<Boolean> = MutableStateFlow(false)
    private val _errorDatabase: MutableStateFlow<Boolean> = MutableStateFlow(false)

    val error: StateFlow<Boolean> = _error
    val errorDatabase: StateFlow<Boolean> = _errorDatabase

    val lat = MutableLiveData(0.0)
    val long = MutableLiveData(0.0)

    fun getWeather(lon: Double, lat: Double) {
        viewModelScope.launch(Dispatchers.IO) {
            val weatherData = weatherRepository.getWeatherData(lon, lat)
            if (weatherData != null) {
                _weatherData.value = weatherData
                _error.value = false
                _errorDatabase.value = false
            } else {
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
        viewModelScope.launch{
            val savedWeatherData = weatherRepository.getSavedWeatherData()

            if (savedWeatherData != null) {
                _weatherData.value = savedWeatherData
                _errorDatabase.value = false
            } else {
                Log.e("WeatherViewModel", "No saved weather data found")
                _errorDatabase.value = true
            }
        }
    }
}
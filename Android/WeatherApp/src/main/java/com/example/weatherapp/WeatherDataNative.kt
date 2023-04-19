// Paketdeklaration för det här exemplet
package com.example.weatherapp

// Importera nödvändiga bibliotek och komponenter från Jetpack Compose
import androidx.compose.runtime.mutableStateListOf

class WeatherDataNative {

    // Define the Weather data class
    data class Weather(
        val city: String,
        val temperature: String,
        val weekDay: String,
        val loadData: Boolean,
        val date: String,
        val prognosImage: String,
    )

    // Define some dummy weather data
    val dummyWeatherData = listOf(
        Weather("Stockholm", "-4°C", "Tue",true, "2023-03-28","snow"),
        Weather("Stockholm", "12°C","Wed",true,"2023-03-29","sun"),
        Weather("Stockholm", "2°C","Thur",true,"2023-03-30","cloud"),
        Weather("Stockholm", "1°C","Fri",true,"2023-03-31","rain"),
        Weather("Stockholm", "13°C","Sat",true,"2023-04-01","sun"),
        Weather("Stockholm", "8°C","Sun",true,"2023-04-02","sun")
    )

    // Define some private variables for the class
    private var city_name: String = ""
    private var temperature: String = ""
    private var weekDay: String = ""
    private var loadData: Boolean = false
    private var date: String = ""
    private var prognosImage: String = ""

    // Create a mutable list of weather data using the Jetpack Compose mutableStateListOf class
    private val weatherList = mutableStateListOf<Weather>()

    // Define a companion object to load the JNI bridge library
    companion object {
        init {
            System.loadLibrary("JniBridge")
        }
    }

    // Initialize the class and create a Weather object for each item in the dummyWeatherData list
    init {
        for (data in dummyWeatherData) {
            val weatherObject = createWeatherObjectFromC(
                data.city,
                data.temperature,
                data.weekDay,
                data.loadData,
                data.date,
                data.prognosImage)

            val weather = Weather(
                getCityName(weatherObject),
                getTemperature(weatherObject),
                getWeekDay(weatherObject),
                getLoadData(weatherObject),
                getDate(weatherObject),
                getPrognosImage(weatherObject))

            weatherList.add(weather)
        }
    }

    // Define a function to return the list of weather data
    fun getWeatherList(): List<Weather> {
        return weatherList
    }

    // Define some external functions to interface with the C code
    external fun createWeatherObjectFromC(
        cityName: String,
        temperature: String,
        weekDay: String,
        loadData: Boolean,
        date: String,
        prognosImage: String): WeatherDataNative

    external fun getCityName(data: WeatherDataNative): String
    external fun setCityName(data: WeatherDataNative, cityName: String)
    external fun getTemperature(data: WeatherDataNative): String
    external fun setTemperature(data: WeatherDataNative, temperature: String)
    external fun getWeekDay(data: WeatherDataNative): String
    external fun setWeekDay(data: WeatherDataNative, weekDay: String)
    external fun getLoadData(data: WeatherDataNative): Boolean
    external fun setLoadData(data: WeatherDataNative, loadData: Boolean)
    external fun getDate(data: WeatherDataNative): String
    external fun setDate(data: WeatherDataNative, date: String)
    external fun getPrognosImage(data: WeatherDataNative): String
    external fun setPrognosImage(data: WeatherDataNative, date: String)
}

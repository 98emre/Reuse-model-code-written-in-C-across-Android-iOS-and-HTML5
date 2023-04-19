package com.example.weatherappwithoutc

class WeatherData {

    // Dataklass Weather för att lagra väderinformation
    data class Weather(
        val city: String,
        val temperature: String,
        val weekDay: String,
        val loadData: Boolean,
        val date: String,
        val prognosImage: String
    )

    // Skapa en lista
    val dummyWeatherData = listOf(
        Weather("Stockholm", "-4°C", "Tue",true, "2023-03-28","snow"),
        Weather("Stockholm", "12°C","Wed",true,"2023-03-29","sun"),
        Weather("Stockholm", "2°C","Thur",true,"2023-03-30","cloud"),
        Weather("Stockholm", "1°C","Fri",true,"2023-03-31","rain"),
        Weather("Stockholm", "13°C","Sat",true,"2023-04-01","sun"),
        Weather("Stockholm", "8°C","Sun",true,"2023-04-02","sun")
    )

    // Skapa en MutableList för att lagra Weather-objekt
    private val weatherList = mutableListOf<Weather>()

    // Initieringsblock som körs när klassen
    init {
        // Loopa igenom dummyWeatherData och lägg till varje post i weatherList
        for (data in dummyWeatherData) {
            val weather = Weather(
                data.city,
                data.temperature,
                data.weekDay,
                data.loadData,
                data.date,
                data.prognosImage
            )
            weatherList.add(weather)
        }
    }

    // Funktion för att returnera weatherList
    fun getWeatherList(): List<Weather> {
        return weatherList
    }
}

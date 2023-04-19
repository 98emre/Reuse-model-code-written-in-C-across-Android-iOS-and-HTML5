package com.example.weatherappwithoutc

import androidx.compose.foundation.layout.*
import androidx.compose.material.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.unit.dp

// kompositionsfunktion för WeatherView som tar emot en lista med väderdata
@Composable
fun WeatherView(weatherList: List<WeatherData.Weather>) {
    // Skapa en kolumn som innehåller alla rader med väderinformation
    Column(modifier = Modifier.padding(10.dp)) {
        // Lägg till en tom rad
        Spacer(modifier = Modifier.height(10.dp))

        // Loopa igenom alla väderposter i listan och skapa en rad för varje post
        for (weather in weatherList) {
            Row {
                // Skapa en kolumn med stadens namn och datumet för vädret
                Column {
                    Text(text = weather.city + " ")
                    Text(text = weather.date)
                }

                // Lägg till textkomponenter för variablerna
                Text(text = weather.temperature + " ")
                Text(text = weather.weekDay + " ")
                Text(text = "${weather.loadData}" + " ")
                Text(text = weather.prognosImage)
            }

            Spacer(modifier = Modifier.height(20.dp))
        }
    }
}

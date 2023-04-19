package com.example.weatherappwithoutc

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.layout.*
import androidx.compose.material.MaterialTheme
import androidx.compose.material.Surface
import androidx.compose.ui.Modifier
import com.example.weatherappwithoutc.ui.theme.WeatherAppWithoutCTheme

// Main klassen för applikationen
class MainActivity : ComponentActivity() {

    // Skapa en instans av WeatherData klassen
    private val weatherData: WeatherData = WeatherData()

    // Funktionen onCreate körs när aktiviteten skapas
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        // Ange innehåll för aktiviteten genom att använda Jetpack Compose
        setContent {
            // Använd temat för att styla komponenterna
            WeatherAppWithoutCTheme {
                // Skapa en yta som fyller hela skärmen och använder temats bakgrundsfärg
                Surface(
                    modifier = Modifier.fillMaxSize(),
                    color = MaterialTheme.colors.background
                ) {
                    // Anropa WeatherView funktionen och skicka in en lista med väderdata
                    WeatherView(weatherData.getWeatherList())
                }
            }
        }
    }
}


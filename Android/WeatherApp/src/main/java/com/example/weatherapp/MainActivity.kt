// Paketdeklaration för det här exemplet
package com.example.weatherapp

// Importera nödvändiga bibliotek och komponenter från Jetpack Compose
import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material.MaterialTheme
import androidx.compose.material.Surface
import androidx.compose.ui.Modifier
import com.example.weatherapp.ui.theme.WeatherAppTheme

// Huvudsakliga aktivitetsklassen för appen
class MainActivity : ComponentActivity() {
    // Skapa en instans av WeatherDataNative för att hämta väderdata
    private val weatherData = WeatherDataNative()

    // onCreate funktionen för aktivitete
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        // Sätt innehållet för aktiviteten med Jetpack Compose
        setContent {
            WeatherAppTheme {
                // A surface container using the 'background' color from the theme
                Surface(modifier = Modifier.fillMaxSize(), color = MaterialTheme.colors.background)
                {
                    // Visa väderdata med hjälp av WeatherView komponenten
                    WeatherView(weatherList = weatherData.getWeatherList())
                }
            }
        }
    }
}


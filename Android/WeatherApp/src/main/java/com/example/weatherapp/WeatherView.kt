// Paketdeklaration för det här exemplet
package com.example.weatherapp

// Importera nödvändiga bibliotek och komponenter från Jetpack Compose
import androidx.compose.foundation.layout.*
import androidx.compose.material.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.unit.dp

// En kompositör för att visa väderinformation baserat på en lista med WeatherDataNative.Weather-objekt
@Composable
fun WeatherView(weatherList: List<WeatherDataNative.Weather>) {
    // Skapa en kolumnlayout med 10 dp ytterkant runt den
    Column(modifier = Modifier.padding(10.dp)) {
        // Lägg till en tom plats på 10 dp höjd
        Spacer(modifier = Modifier.height(10.dp))

        // Loopa igenom varje väderobjekt i listan
        for (weather in weatherList) {
            // Skapa en radlayout för varje väderobjekt
            Row {
                // Skapa en kolumnlayout för att visa stad och datum vertikalt
                Column {
                    Text(text = weather.city + " ")
                    Text(text = weather.date)
                }

                // Lägg till text för att visa temperatur, veckodag, loadData och prognosbild
                Text(text = weather.temperature + " ")
                Text(text = weather.weekDay + " ")
                Text(text = "${weather.loadData}" + " ")
                Text(text = weather.prognosImage)
            }
            // Lägg till en tom plats på 20 dp höjd mellan varje rad
            Spacer(modifier = Modifier.height(20.dp))
        }
    }
}

package com.example.weatherappwithoutc

import android.annotation.SuppressLint
import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.foundation.text.KeyboardOptions
import androidx.compose.material.*
import androidx.compose.runtime.*
import androidx.compose.ui.Modifier
import androidx.compose.ui.platform.LocalFocusManager
import androidx.compose.ui.text.input.KeyboardType
import androidx.compose.ui.unit.dp
import com.example.weatherappwithoutc.ui.theme.WeatherAppWithoutCTheme

class MainActivity : ComponentActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        setContent {
            WeatherAppWithoutCTheme {
                Surface(
                    modifier = Modifier.fillMaxSize(),
                    color = MaterialTheme.colors.background
                ) {
                    WeatherScreen()
                }
            }
        }
    }
}

@SuppressLint("UnusedMaterialScaffoldPaddingParameter", "StateFlowValueCalledInComposition")
@Composable
fun WeatherScreen() {
    val weather = WeatherData("2022-05-08 22:00")
    val dummyData = remember { DummyData(weather) }

    var lat by remember { mutableStateOf(0.0) }
    var long by remember { mutableStateOf(0.0) }

    weather.lon = lat
    weather.lat = long

    Scaffold(
        topBar = {
            TopAppBar(title = {
                Text("Weather Forecast Dummy")
            })
        }
    ) {

        Column(modifier = Modifier.padding(10.dp)) {
            LocationInput(onSubmit = { submittedLat, submittedLong ->
                lat = submittedLat
                long = submittedLong
            }, lat = lat, long = long)

            Text("Lat: ${weather.lat}")
            Text("Lon: ${weather.lon}")
            Text("ApprovedTime: ${weather.approvedTime}")
            Divider()

            Spacer(modifier = Modifier.height(16.dp))

            LazyColumn{
                items(dummyData.getAllDummyData()) { hourlyData ->
                    Column(modifier = Modifier.padding(10.dp)) {
                        HourlyDataRow(hourlyData)
                        Divider()
                    }
                }
            }

        }
    }
}

@Composable
fun HourlyDataRow(hourlyData: WeatherData.HourlyWeatherData) {
    Text("${hourlyData.time}")
    Row {
        Text("${hourlyData.temperature} °C")
        Text("${hourlyData.icon} °C")
    }
}

@Composable
fun LocationInput(onSubmit: (Double, Double) -> Unit, lat: Double, long: Double) {
    var latStr by remember { mutableStateOf(lat.toString()) }
    var longStr by remember { mutableStateOf(long.toString()) }

    val focusManager = LocalFocusManager.current

    Column(modifier = Modifier.padding(16.dp)) {
        OutlinedTextField(
            value = longStr,
            onValueChange = { longStr = it },
            label = { Text("Longitude") },
            modifier = Modifier.fillMaxWidth(),
            keyboardOptions = KeyboardOptions(keyboardType = KeyboardType.Number)
        )

        Spacer(modifier = Modifier.height(16.dp))

        OutlinedTextField(
            value = latStr,
            onValueChange = { latStr = it },
            label = { Text("Latitude") },
            modifier = Modifier.fillMaxWidth(),
            keyboardOptions = KeyboardOptions(keyboardType = KeyboardType.Number)
        )

        Spacer(modifier = Modifier.height(16.dp))
        Button(
            onClick = {
                onSubmit(latStr.toDouble(), longStr.toDouble())
                focusManager.clearFocus() // Flytta fokus från textfälten
            }
        ) {
            Text("Submit")
        }
    }
}


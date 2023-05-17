package com.example.weatherapp

import android.annotation.SuppressLint
import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.text.KeyboardOptions
import androidx.compose.material.*
import androidx.compose.runtime.*
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.platform.LocalFocusManager
import androidx.compose.ui.text.input.KeyboardType
import androidx.compose.ui.unit.dp
import com.example.weatherapp.ui.theme.WeatherAppTheme


class MainActivity : ComponentActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        setContent {
            WeatherAppTheme {
                Surface(
                    modifier = Modifier.fillMaxSize(),
                    color = MaterialTheme.colors.background
                ) {
                    Column(
                        modifier = Modifier.fillMaxSize(),
                        verticalArrangement = Arrangement.Center,
                        horizontalAlignment = Alignment.CenterHorizontally
                    ) {


                        WeatherScreen()


                    }
                }
            }
        }
    }
}

@SuppressLint("UnusedMaterialScaffoldPaddingParameter", "StateFlowValueCalledInComposition")
@Composable
fun WeatherScreen() {
    val weatherNative = remember { WeatherNative() }
    val dummyData = remember { DummyData(weatherNative) }

    val data = weatherNative.createWeatherObjectFromC("2022-05-08 22:00")
    dummyData.getAllDummyData(data)

    val approvedTime = weatherNative.getApprovedTime(data)

    var lat by remember { mutableStateOf(0.0) }
    var long by remember { mutableStateOf(0.0) }

    weatherNative.setLat(data, lat)
    weatherNative.setLon(data, long)

    val submittedState = remember { mutableStateOf(false) }

    Scaffold(
        topBar = {
            TopAppBar(title = {
                Text("Weather Forecast C Dummy")
            })
        }
    ) {
        Column(modifier = Modifier.padding(10.dp)) {
            LocationInput(
                onSubmit = { submittedLat, submittedLong ->
                    lat = submittedLat
                    long = submittedLong
                },
                lat = lat,
                long = long,
                onSubmitButtonClick = {
                    submittedState.value = true
                }
            )

            Text("Lat: ${weatherNative.getLat(data)}")
            Text("Lon: ${weatherNative.getLon(data)}")

            Text("ApprovedTime: ${approvedTime}")
            Divider()

            Spacer(modifier = Modifier.height(16.dp))

            if (submittedState.value) {

                val startTime = System.nanoTime()

                LazyColumn {
                    items(weatherNative.getHourlyDataSize(data)) { index ->
                        val hourlyData = weatherNative.getHourlyData(data, index)
                        Column(modifier = Modifier.padding(10.dp)) {
                            HourlyDataRow(hourlyData)
                            Divider()
                        }
                    }
                }


                val endTime = System.nanoTime()

                val executionTime = endTime - startTime
                println("Execution time: $executionTime ms")

                val executionTimeInMillis = executionTime / 1_000_000
                println("Execution time: $executionTimeInMillis milliseconds")

            }
        }
    }
}

@Composable
fun HourlyDataRow(data: WeatherNative.HourlyWeatherData) {
    Text(text = "${data.time}")
    Row {
        Text(text = " ${data.temperature} °C")
        Text(text = " ${data.icon}")
    }
}

@Composable
fun LocationInput(
    onSubmit: (Double, Double) -> Unit,
    lat: Double,
    long: Double,
    onSubmitButtonClick: () -> Unit
) {
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
                onSubmitButtonClick() // Markera att användaren har tryckt på "Submit"
            }
        ) {
            Text("Submit")
        }
    }
}








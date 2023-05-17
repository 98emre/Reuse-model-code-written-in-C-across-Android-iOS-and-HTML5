package com.example.weatherappcapi

import android.annotation.SuppressLint
import android.content.res.Configuration
import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.text.KeyboardOptions
import androidx.compose.material.*
import androidx.compose.runtime.*
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.text.input.KeyboardType
import androidx.compose.foundation.Image
import androidx.compose.foundation.text.KeyboardActions
import androidx.compose.runtime.saveable.rememberSaveable
import androidx.compose.ui.ExperimentalComposeUiApi
import androidx.compose.ui.platform.*
import androidx.compose.ui.text.input.ImeAction
import androidx.compose.ui.unit.dp
import androidx.lifecycle.viewmodel.compose.viewModel
import com.example.weatherappcapi.Model.WeatherViewModel
import com.example.weatherappcapi.ui.theme.WeatherAppCAPITheme
import com.example.weatherappcapi.utils.getWeatherSymbolDrawableName
import com.example.weatherappcapi.utils.isDayTime
import dagger.hilt.android.AndroidEntryPoint
import java.util.*

@AndroidEntryPoint
class MainActivity : ComponentActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            WeatherAppCAPITheme {
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

@SuppressLint("UnusedMaterialScaffoldPaddingParameter")
@Composable
fun WeatherScreen(weatherViewModel: WeatherViewModel = viewModel()) {
    val weatherData by weatherViewModel.weatherData.collectAsState()
    val weatherDataSize by weatherViewModel.weatherDataSize.collectAsState()
    val showErrorForSearch by weatherViewModel.error.collectAsState()
    val showErrorForDatabase by weatherViewModel.errorDatabase.collectAsState()

    var lat by remember { mutableStateOf(0.0) }
    var long by remember { mutableStateOf(0.0) }

    val config = LocalConfiguration.current
    val portTraitMode = remember { mutableStateOf(config.orientation) }

    LaunchedEffect(Unit) {
        weatherViewModel.getSavedWeatherData()
        weatherViewModel.printAllData()
    }

    Scaffold(
        topBar = {
            TopAppBar(title = {
                Text("Weather Forecast C API")
            })
        }
    ) {

        Column(modifier = Modifier.padding(16.dp)) {
            if (showErrorForSearch) {
                Text("An error occurred while loading weather data.", color = Color.Red)
            }

            if (showErrorForDatabase) {
                Text("You have empty database", color = Color.Red)
            }

            if (weatherData != null) {
                Text(
                    text = "ApprovedTime: ${weatherData!!.getApprovedTime(weatherData!!)}\n" +
                            "Longitude: ${weatherData!!.getLon(weatherData!!)}\n" +
                            "Latitude: ${weatherData!!.getLat(weatherData!!)}"
                )
                Divider()
            }

                if (portTraitMode.value == Configuration.ORIENTATION_PORTRAIT) {
                    DisplayPortrait(weatherDataSize, weatherData, lat, long, weatherViewModel)

                } else{
                    DisplayLandscape(weatherDataSize, weatherData, lat, long, weatherViewModel)

                }
        }
    }
}

@Composable
private fun DisplayPortrait(
    weatherDataSize: Int?,
    weatherData: WeatherNative?,
    lat: Double,
    long: Double,
    weatherViewModel: WeatherViewModel
) {
    var lat1 = lat
    var long1 = long
    Column {
        Box(modifier = Modifier.weight(1f)) {
            LazyColumn {
                items(weatherDataSize ?: 0) { i ->
                    val data = weatherData!!.getHourlyData(weatherData!!, i)
                    Column(modifier = Modifier.padding(10.dp)) {
                        HourlyDataRow(data)
                        Divider()
                    }
                }
            }
        }
        LocationInput(onSubmit = { submittedLat, submittedLong ->
            lat1 = submittedLat
            long1 = submittedLong
            weatherViewModel.getWeather(long1, lat1)
        }, lat = lat1, long = long1)
    }
}

@Composable
private fun DisplayLandscape(
    weatherDataSize: Int?,
    weatherData: WeatherNative?,
    lat: Double,
    long: Double,
    weatherViewModel: WeatherViewModel
) {
    var lat1 = lat
    var long1 = long

    Row {
        LazyColumn(modifier = Modifier
            .fillMaxHeight()
            .weight(0.7f)){
                items(weatherDataSize ?: 0) { i ->
                    val data = weatherData!!.getHourlyData(weatherData!!, i)
                    Column(modifier = Modifier.padding(10.dp)) {
                        HourlyDataRow(data)
                        Divider()
                    }
                }
            }
        LocationInput(onSubmit = { submittedLat, submittedLong ->
            lat1 = submittedLat
            long1 = submittedLong
            weatherViewModel.getWeather(long1, lat1)
        }, lat = lat1, long = long1,
            modifier = Modifier
                .fillMaxHeight()
                .weight(0.5f))
    }
}


@Composable
fun HourlyDataRow(data: WeatherNative.HourlyWeatherData) {
    Text(text = "${data.time}")
    Row {
        val resourceId = LocalContext.current.resources.getIdentifier(
            getWeatherSymbolDrawableName(data.icon, isDayTime(data.time)),
            "drawable",
            LocalContext.current.packageName
        )

        Image(
            painter = painterResource(id = resourceId),
            contentDescription = null,
            modifier = Modifier.size(60.dp)
        )

        Text(text = " ${data.temperature} °C")
    }
}

@OptIn(ExperimentalComposeUiApi::class)
@Composable
fun LocationInput(
    onSubmit: (Double, Double) -> Unit,
    lat: Double,
    long: Double,
    modifier: Modifier = Modifier
    ) {
    var latStr by remember { mutableStateOf(lat.toString()) }
    var longStr by remember{ mutableStateOf(long.toString()) }
    val focusManager = LocalFocusManager.current
    val submitEnabled = latStr.toDoubleOrNull() != null && longStr.toDoubleOrNull() != null

    val keyboardController = LocalSoftwareKeyboardController.current

    Column(modifier = modifier.padding(16.dp)) {
        Row(Modifier.fillMaxWidth()) {
            OutlinedTextField(
                value = longStr,
                onValueChange = { longStr = it },
                label = { Text("Longitude") },
                modifier = Modifier.weight(1f),
                keyboardOptions = KeyboardOptions(
                    keyboardType = KeyboardType.Number,
                    imeAction = ImeAction.Done
                ),
                keyboardActions = KeyboardActions(onDone = { keyboardController?.hide() }),
                maxLines = 1
            )
            Spacer(modifier = Modifier.width(16.dp))

            OutlinedTextField(
                value = latStr,
                onValueChange = { latStr = it },
                label = { Text("Latitude") },
                modifier = Modifier.weight(1f),
                keyboardOptions = KeyboardOptions(
                    keyboardType = KeyboardType.Number,
                    imeAction = ImeAction.Done
                ),
                keyboardActions = KeyboardActions(onDone = { keyboardController?.hide() }),
                maxLines = 1
            )
        }

        if (!submitEnabled) {
            Text("Please enter valid latitude and longitude values", color = Color.Red)
        }

        Button(
            onClick = {
                if (submitEnabled) {
                    onSubmit(latStr.toDouble(), longStr.toDouble())
                    focusManager.clearFocus()
                }
            },
            enabled = submitEnabled
        ) {
            Text("Submit")
        }
    }
}



package com.example.weatherappapi

import android.annotation.SuppressLint
import android.content.res.Configuration
import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.Image
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.foundation.text.KeyboardActions
import androidx.compose.foundation.text.KeyboardOptions
import androidx.compose.material.*
import androidx.compose.runtime.*
import androidx.compose.runtime.saveable.rememberSaveable
import androidx.compose.ui.ExperimentalComposeUiApi
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.platform.*
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.text.input.ImeAction
import androidx.compose.ui.text.input.KeyboardType
import androidx.compose.ui.unit.dp
import androidx.hilt.navigation.compose.hiltViewModel
import com.example.weatherappapi.Data.WeatherData
import com.example.weatherappapi.Model.WeatherViewModel
import com.example.weatherappapi.ui.theme.WeatherAppAPITheme
import com.example.weatherappapi.utils.getWeatherSymbolDrawableName
import com.example.weatherappapi.utils.isDayTime
import dagger.hilt.android.AndroidEntryPoint

@AndroidEntryPoint
class MainActivity : ComponentActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        setContent {
            WeatherAppAPITheme {
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
fun WeatherScreen(weatherViewModel: WeatherViewModel = hiltViewModel()) {

    val weatherData by weatherViewModel._weatherData.collectAsState()
    var lat = remember{ mutableStateOf(0.0) }
    var long = remember { mutableStateOf(0.0) }

    val showErrorForSearch by weatherViewModel.error.collectAsState()
    val showErrorForEmptyDatabase by weatherViewModel.errorDatabase.collectAsState()

    val config = LocalConfiguration.current
    val portTraitMode = remember { mutableStateOf(config.orientation) }


    LaunchedEffect(Unit) { // Kör först när composable blir synlig
        weatherViewModel.getSavedWeatherData()
    }

    Scaffold(
        topBar = {
            TopAppBar(title = {
                Text("Weather Forecast API")
            })
        }
    ) {
        Column(modifier = Modifier.padding(10.dp)) {

        if (showErrorForSearch) {
            Text("An error occurred while loading weather data.", color = Color.Red)
        }

        if (showErrorForEmptyDatabase) {
            Text("You have empty database", color = Color.Red)
        }

        if (weatherData != null) {

            Text(
                text = "Approved Time:  ${weatherData?.approvedTime}\n" +
                        "Longitude: ${weatherViewModel._weatherData.value?.lon}\n" +
                        "Latitude: ${weatherViewModel._weatherData.value?.lat}\n"
            )

            Divider()
        }

                if (portTraitMode.value == Configuration.ORIENTATION_PORTRAIT) {
                    DisplayPortrait(weatherData, lat, long, weatherViewModel)
                } else {
                    DisplayLandscape(weatherData, lat, long, weatherViewModel)
                }
            }

    }
}

@Composable
private fun DisplayPortrait(
    weatherData: WeatherData?,
    lat: MutableState<Double>,
    long: MutableState<Double>,
    weatherViewModel: WeatherViewModel
) {
    Column {
        Box(modifier = Modifier.Companion.weight(1f)) {
            LazyColumn(modifier = Modifier.fillMaxSize()) {
                items(weatherData?.data ?: emptyList()) { hourlyData ->
                    Column(modifier = Modifier.padding(10.dp)) {
                        HourlyDataRow(hourlyData)
                        Divider()
                    }
                }
            }
        }

        LocationInput(onSubmit = { submittedLat, submittedLong ->
            lat.value = submittedLat
            long.value = submittedLong
            weatherViewModel.getWeather(long.value, lat.value)
        }, lat = lat.value, long = long.value)
    }
}

@Composable
private fun DisplayLandscape(
    weatherData: WeatherData?,
    lat: MutableState<Double>,
    long: MutableState<Double>,
    weatherViewModel: WeatherViewModel
) {
    Row {
        LazyColumn(modifier = Modifier.fillMaxHeight().weight(0.7f))
        {
            items(weatherData?.data ?: emptyList()) { hourlyData ->
                Column(modifier = Modifier.padding(10.dp)) {
                    HourlyDataRow(hourlyData)
                    Divider()
                }
            }
        }

        LocationInput(
            onSubmit = { submittedLat, submittedLong ->
                lat.value = submittedLat
                long.value = submittedLong
                weatherViewModel.getWeather(long.value, lat.value)
            }, lat = lat.value, long = long.value,
            modifier = Modifier.fillMaxHeight().weight(0.3f)
        )
    }
}


@Composable
fun HourlyDataRow(hourlyData: WeatherData.HourlyWeatherData) {
    Text("${hourlyData.time}")
    Row {
        val resourceId = LocalContext.current.resources.getIdentifier(
            getWeatherSymbolDrawableName(hourlyData.icon, isDayTime(hourlyData.time)),
            "drawable",
            LocalContext.current.packageName
        )

        Image(
            painter = painterResource(id = resourceId),
            contentDescription = null,
            modifier = Modifier.size(60.dp)
        )
        Text("${hourlyData.temperature} °C")
    }
}

@OptIn(ExperimentalComposeUiApi::class)
@Composable
fun LocationInput(
    onSubmit: (Double, Double) -> Unit,
    lat: Double?,
    long: Double?,
    modifier: Modifier = Modifier
) {
    var latStr by remember { mutableStateOf(lat.toString()) }
    var longStr by remember { mutableStateOf(long.toString()) }
    val submitEnabled = latStr.toDoubleOrNull() != null && longStr.toDoubleOrNull() != null

    val keyboardController = LocalSoftwareKeyboardController.current

    val focusManager = LocalFocusManager.current
    //val inputService = LocalTextInputService.current

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
                keyboardActions = KeyboardActions(onDone = {keyboardController?.hide()}),
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
                keyboardActions = KeyboardActions(onDone = {keyboardController?.hide()}),
                maxLines = 1
            )
        }

        Spacer(modifier = Modifier.height(16.dp))

        if (!submitEnabled) {
            Text("Please enter valid latitude and longitude values", color = Color.Red)
        }

        Button(
            onClick = {
                if (submitEnabled) {
                    onSubmit(latStr.toDouble(), longStr.toDouble())
                    focusManager.clearFocus()
                   // inputService?.hideSoftwareKeyboard()
                }
            },
            enabled = submitEnabled,
        ) {
            Text("Submit")
        }
    }
}












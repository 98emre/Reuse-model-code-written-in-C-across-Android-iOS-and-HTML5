package com.example.weatherappcapi.Network

import com.example.weatherappcapi.JsonData.Weather
import retrofit2.http.GET
import retrofit2.http.Path

interface WeatherAPI {

    @GET("category/pmp3g/version/2/geotype/point/lon/{lon}/lat/{lat}/data.json")
    suspend fun getWeather(@Path("lon") lon: Double, @Path("lat") lat: Double): Weather
}
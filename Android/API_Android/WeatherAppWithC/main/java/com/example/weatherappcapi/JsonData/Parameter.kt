package com.example.weatherappcapi.JsonData

data class Parameter(
    val level: Int,
    val levelType: String,
    val name: String,
    val unit: String,
    val values: List<Double>
)
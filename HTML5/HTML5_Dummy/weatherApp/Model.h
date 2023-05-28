#ifndef MODEL_H
#define MODEL_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <emscripten.h>

#define MAX_TEMP_LEN 100
#define MAX_APPROVEDTIME_LEN 100
#define MAX_ICON_LEN 100
#define MAX_TIME_LEN 100

typedef struct {
    char time[MAX_TIME_LEN];
    char temperature[MAX_TEMP_LEN];
    char icon[MAX_ICON_LEN];
} HourlyWeatherData;

typedef struct {
    HourlyWeatherData* data;
    char approvedTime[MAX_APPROVEDTIME_LEN];
    int size;
    float lat;
    float lon;
} WeatherData;

EMSCRIPTEN_KEEPALIVE
WeatherData* createWeatherObjectFromC(const char* approvedTime);

EMSCRIPTEN_KEEPALIVE
HourlyWeatherData* getHourlyData(const WeatherData* data, int index);

EMSCRIPTEN_KEEPALIVE
const char* getApprovedTime(const WeatherData* data);

EMSCRIPTEN_KEEPALIVE
void setApprovedTime(WeatherData* data, const char* approvedTime);


EMSCRIPTEN_KEEPALIVE
void addHourlyData(WeatherData* data, HourlyWeatherData* hourlyData);


EMSCRIPTEN_KEEPALIVE
int getHourlyDataSize(const WeatherData* data);


EMSCRIPTEN_KEEPALIVE
float getLat(const WeatherData* data);

EMSCRIPTEN_KEEPALIVE
void setLat(WeatherData* data, float lat);


EMSCRIPTEN_KEEPALIVE
float getLon(const WeatherData* data);

EMSCRIPTEN_KEEPALIVE
void setLon(WeatherData* data, float lon);


EMSCRIPTEN_KEEPALIVE
void freeWeatherObject(WeatherData* obj);

// Hourly Weather


EMSCRIPTEN_KEEPALIVE
HourlyWeatherData* createHourlyWeatherObjectFromC(const char* time, const char* temperature, const char* icon);


EMSCRIPTEN_KEEPALIVE
const char* getTime(const HourlyWeatherData* data);

EMSCRIPTEN_KEEPALIVE
void setTime(HourlyWeatherData* data, const char* hour);


EMSCRIPTEN_KEEPALIVE
const char* getTemperature(const HourlyWeatherData* data);

EMSCRIPTEN_KEEPALIVE
void setTemperature(HourlyWeatherData* data, const char* temperature);


EMSCRIPTEN_KEEPALIVE
const char* getIcon(const HourlyWeatherData* data);

EMSCRIPTEN_KEEPALIVE
void setIcon(HourlyWeatherData* data, const char* icon);

EMSCRIPTEN_KEEPALIVE
void freeHourlyWeatherObject(HourlyWeatherData* obj);


#endif // MODEL_H
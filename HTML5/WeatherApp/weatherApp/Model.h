#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <emscripten.h>


// Konstanter för maximala längder av strängar för structen
#define MAX_CITY_NAME_LEN 100
#define MAX_TEMP_LEN 10
#define MAX_WEEKDAY_LEN 10
#define MAX_DATE_LEN 20
#define MAX_IMAGE_LEN 20

// Structen för att lagra weatherData
typedef struct {
    char city_name[MAX_CITY_NAME_LEN];
    char temperature[MAX_TEMP_LEN];
    char weekDay[MAX_WEEKDAY_LEN];
    bool loadData;
    char date[MAX_DATE_LEN];
    char prognosImage[MAX_IMAGE_LEN];
} WeatherData;

// Funktioner för att arbeta med WeatherData

EMSCRIPTEN_KEEPALIVE
WeatherData* createWeatherObjectFromC(const char* city_name, const char* temperature, 
                                        const char* weekDay, bool loadData, const char* date, const char* prognosImage);

EMSCRIPTEN_KEEPALIVE
const char* getCityName(const WeatherData* data);

EMSCRIPTEN_KEEPALIVE
void setCityName(WeatherData* data, const char* cityName);

EMSCRIPTEN_KEEPALIVE
const char* getTemperature(const WeatherData* data);

EMSCRIPTEN_KEEPALIVE
void setTemperature(WeatherData* data, const char* temperature);

EMSCRIPTEN_KEEPALIVE
const char* getWeekDay(const WeatherData* data);

EMSCRIPTEN_KEEPALIVE
void setWeekDay(WeatherData* data, const char* weekDay);

EMSCRIPTEN_KEEPALIVE
bool getLoadData(const WeatherData* data);

EMSCRIPTEN_KEEPALIVE
void setLoadData(WeatherData* data, bool loadData);

EMSCRIPTEN_KEEPALIVE
const char* getDate(const WeatherData* data);

EMSCRIPTEN_KEEPALIVE
void setDate(WeatherData* data, const char* date);

EMSCRIPTEN_KEEPALIVE
const char* getPrognosImage(const WeatherData* data);

EMSCRIPTEN_KEEPALIVE
void setPrognosImage(WeatherData* data, const char* prognosImage);

EMSCRIPTEN_KEEPALIVE
void freeWeatherObject(WeatherData* obj);


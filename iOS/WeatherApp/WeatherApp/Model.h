// Detta är en headerfil som definierar structen WeatherData och funktionsprototyperna för att arbeta med den.
// Den definierar också vissa konstanter som används för att sätta maximal längd på strängar inom structen.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CITY_NAME_LEN 100
#define MAX_TEMP_LEN 10
#define MAX_WEEKDAY_LEN 10
#define MAX_DATE_LEN 20
#define MAX_IMAGE_LEN 20

// Struct som håller weather data
typedef struct {
char city_name[MAX_CITY_NAME_LEN];
char temperature[MAX_TEMP_LEN];
char weekDay[MAX_WEEKDAY_LEN];
bool loadData;
char date[MAX_DATE_LEN];
char prognosImage[MAX_IMAGE_LEN];
} WeatherData;

// Funktion prototypes för arbeta ,ed WeatherData objekt
WeatherData* createWeatherObjectFromC(const char* city_name, const char* temperature,
const char* weekDay, bool loadData, const char* date, const char* prognosImage);

const char* getCityName(const WeatherData* data);
void setCityName(WeatherData* data, const char* cityName);

const char* getTemperature(const WeatherData* data);
void setTemperature(WeatherData* data, const char* temperature);

const char* getWeekDay(const WeatherData* data);
void setWeekDay(WeatherData* data, const char* weekDay);

bool getLoadData(const WeatherData* data);
void setLoadData(WeatherData* data, bool loadData);

const char* getDate(const WeatherData* data);
void setDate(WeatherData* data, const char* date);

const char* getPrognosImage(const WeatherData* data);
void setPrognosImage(WeatherData* data, const char* prognosImage);

void freeWeatherObject(WeatherData* obj);

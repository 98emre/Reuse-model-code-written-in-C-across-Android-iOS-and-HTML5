#ifndef MODEL_H
#define MODEL_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_TEMP_LEN 10
#define MAX_WEEKDAY_LEN 10
#define MAX_DATE_LEN 20
#define MAX_IMAGE_LEN 20
#define MAX_CITY_NAME_LEN 100


typedef struct {
    char temperature[MAX_TEMP_LEN];
    char weekDay[MAX_WEEKDAY_LEN];
    bool loadData;
    char date[MAX_DATE_LEN];
    char prognosImage[MAX_IMAGE_LEN];
} WeatherData; 

typedef struct {
    WeatherData* data;
    char city_name[MAX_CITY_NAME_LEN];
    int size;
    int capacity;
} WeatherList;



WeatherData* createWeatherObjectFromC(const char* temperature,
                                      const char* weekDay,
                                      bool loadData,
                                      const char* date,
                                      const char* prognosImage);

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


WeatherList* createWeatherList(const char* city_name, int capacity);

const char* getCityName(const WeatherList* list);
void setCityName(WeatherList* list, const char* cityName);

void addWeatherData(WeatherList* list, WeatherData* data);

WeatherData* getWeatherData(const WeatherList* list, int index);

int getWeatherListSize(const WeatherList* list);

void freeWeatherList(WeatherList* list);


#endif // MODEL_H

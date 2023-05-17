#ifndef MODEL_H
#define MODEL_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

WeatherData* createWeatherObjectFromC(const char* approvedTime);

HourlyWeatherData* getHourlyData(const WeatherData* data, int index);

const char* getApprovedTime(const WeatherData* data);
void setApprovedTime(WeatherData* data, const char* approvedTime);

void addHourlyData(WeatherData* data, HourlyWeatherData* hourlyData);
int getHourlyDataSize(const WeatherData* data);

float getLat(const WeatherData* data);
void setLat(WeatherData* data, float lat);

float getLon(const WeatherData* data);
void setLon(WeatherData* data, float lon);

void freeWeatherObject(WeatherData* obj);

// Hourly Weather

HourlyWeatherData* createHourlyWeatherObjectFromC(const char* time, const char* temperature, const char* icon);


const char* getTime(const HourlyWeatherData* data);
void setTime(HourlyWeatherData* data, const char* hour);

const char* getTemperature(const HourlyWeatherData* data);

void setTemperature(HourlyWeatherData* data, const char* temperature);
const char* getIcon(const HourlyWeatherData* data);

void setIcon(HourlyWeatherData* data, const char* icon);

void freeHourlyWeatherObject(HourlyWeatherData* obj);



#endif // MODEL_H

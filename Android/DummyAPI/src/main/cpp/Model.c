#include "Model.h"

WeatherData* createWeatherObjectFromC(const char* approvedTime) {

    WeatherData* obj = malloc(sizeof(WeatherData));

    strncpy(obj->approvedTime, approvedTime, MAX_APPROVEDTIME_LEN);
    obj->approvedTime[MAX_APPROVEDTIME_LEN - 1] = '\0';

    obj->size = 0;
    obj->data = NULL;

    return obj;
}

HourlyWeatherData* getHourlyData(const WeatherData* data, int index){
    if (index < 0 || index >= data->size) {
        return NULL;
    }

    return &data->data[index];
}


const char* getApprovedTime(const WeatherData* data){
    return data->approvedTime;
}

void setApprovedTime(WeatherData* data, const char* approvedTime){
    strncpy(data->approvedTime, approvedTime, MAX_APPROVEDTIME_LEN);
    data->approvedTime[MAX_APPROVEDTIME_LEN - 1] = '\0';
}

void addHourlyData(WeatherData* data, HourlyWeatherData* hourlyData) {
    data->size++;
    data->data = realloc(data->data, data->size * sizeof(HourlyWeatherData));
    data->data[data->size - 1] = *hourlyData;
}


int getHourlyDataSize(const WeatherData* data) {
    return data->size;
}

float getLat(const WeatherData* data) {
    return data->lat;
}

void setLat(WeatherData* data, float lat) {
    data->lat = lat;
}

float getLon(const WeatherData* data) {
    return data->lon;
}

void setLon(WeatherData* data, float lon) {
    data->lon = lon;
}

void freeWeatherObject(WeatherData* obj) {
    free(obj->data);
    free(obj);
}

// Hourly Weather Data

HourlyWeatherData* createHourlyWeatherObjectFromC(const char* time, const char* temperature, const char* icon) {
    HourlyWeatherData* obj = (HourlyWeatherData*) malloc(sizeof(HourlyWeatherData));

    strncpy(obj->time, time, MAX_TIME_LEN);
    obj->time[MAX_TIME_LEN - 1] = '\0';

    strncpy(obj->temperature, temperature, MAX_TEMP_LEN);
    obj->temperature[MAX_TEMP_LEN - 1] = '\0';

    strncpy(obj->icon, icon, MAX_ICON_LEN);
    obj->icon[MAX_ICON_LEN - 1] = '\0';

    return obj;
}

const char* getTime(const HourlyWeatherData* data){
    return data->time;
}

void setTime(HourlyWeatherData* data, const char* time){
    strncpy(data->time, time, MAX_TIME_LEN);
    data->time[MAX_TIME_LEN - 1] = '\0';
}

const char* getTemperature(const HourlyWeatherData* data){
    return data->temperature;
}

void setTemperature(HourlyWeatherData* data, const char* temperature){
    strncpy(data->temperature, temperature, MAX_TEMP_LEN);
    data->temperature[MAX_TEMP_LEN - 1] = '\0';
}

const char* getIcon(const HourlyWeatherData* data){
    return data->icon;
}

void setIcon(HourlyWeatherData* data, const char* icon){
    strncpy(data->icon, icon, MAX_ICON_LEN);
    data->icon[MAX_ICON_LEN - 1] = '\0';
}

void freeHourlyWeatherObject(HourlyWeatherData* obj) {
    free(obj);
}




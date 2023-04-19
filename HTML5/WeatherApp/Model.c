#include "Model.h"
#include <emscripten.h>

// Funktion för att skapa ett WeatherData C objekt från parametrar
WeatherData* createWeatherObjectFromC(const char* city_name, const char* temperature, 
                                        const char* weekDay, bool loadData, const char* date,const char* prognosImage) {

    WeatherData* obj = (WeatherData*) malloc(sizeof(WeatherData));
    
    strncpy(obj->city_name, city_name, MAX_CITY_NAME_LEN);
    obj->city_name[MAX_CITY_NAME_LEN - 1] = '\0';
    
    strncpy(obj->temperature, temperature, MAX_TEMP_LEN);
    obj->temperature[MAX_TEMP_LEN - 1] = '\0';

    strncpy(obj->weekDay, weekDay, MAX_WEEKDAY_LEN);
    obj->weekDay[MAX_WEEKDAY_LEN - 1] = '\0';
    
    obj->loadData = loadData;

    strncpy(obj->date, date, MAX_DATE_LEN);
    obj->date[MAX_DATE_LEN - 1] = '\0';

    strncpy(obj->prognosImage, prognosImage, MAX_IMAGE_LEN);
    obj->prognosImage[MAX_IMAGE_LEN - 1] = '\0';

    return obj;
}

// Hämta city_name från WeatherData C objekt
const char* getCityName(const WeatherData* data) {
    return data->city_name;
}

// Sätt city_name för WeatherData C objekt
void setCityName(WeatherData* data, const char* cityName) {
    strncpy(data->city_name, cityName, MAX_CITY_NAME_LEN);
    data->city_name[MAX_CITY_NAME_LEN - 1] = '\0';
}

// Hämta city_name från WeatherData C objekt
const char* getTemperature(const WeatherData* data) {
    return data->temperature;
}

// Sätt temperature för WeatherData C objekt
void setTemperature(WeatherData* data, const char* temperature) {
    strncpy(data->temperature, temperature, MAX_TEMP_LEN);
    data->temperature[MAX_TEMP_LEN - 1] = '\0';
}

// Hämta weekDay från WeatherData C objekt
const char* getWeekDay(const WeatherData* data){
    return data->weekDay;
}

void setWeekDay(WeatherData* data, const char* weekDay){
    strncpy(data->weekDay, weekDay, MAX_WEEKDAY_LEN);
    data->weekDay[MAX_WEEKDAY_LEN - 1] = '\0';
}

// Hämta loadData från WeatherData C objekt
bool getLoadData(const WeatherData* data) {
    return data->loadData;
}

// Sätt loadData för WeatherData C objekt
void setLoadData(WeatherData* data, bool loadData) {
    data->loadData = loadData;
}

// Hämta date från WeatherData C objekt
const char* getDate(const WeatherData* data){
    return data->date;
}

// Sätt date för WeatherData C objekt
void setDate(WeatherData* data, const char* date){
    strncpy(data->date, date, MAX_DATE_LEN);
    data->date[MAX_DATE_LEN - 1] = '\0';
}

// Hämta prognosImage från WeatherData C objekt
const char* getPrognosImage(const WeatherData* data){
    return data->prognosImage;
}

// Sätt prognosImage för WeatherData C objekt
void setPrognosImage(WeatherData* data, const char* prognosImage){
    strncpy(data->prognosImage, prognosImage, MAX_IMAGE_LEN);
    data->prognosImage[MAX_IMAGE_LEN - 1] = '\0';
}

// Frigör minnet för WeatherData C objekt
void freeWeatherObject(WeatherData* obj) {
    free(obj);
}




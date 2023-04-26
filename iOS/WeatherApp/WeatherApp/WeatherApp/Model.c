#include "Model.h"

// Weather Item 
WeatherData* createWeatherObjectFromC(const char* temperature, const char* weekDay, bool loadData,
                                        const char* date,const char* prognosImage) {

    WeatherData* obj = (WeatherData*) malloc(sizeof(WeatherData));
    
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


const char* getTemperature(const WeatherData* data) {
    return data->temperature;
}

void setTemperature(WeatherData* data, const char* temperature) {
    strncpy(data->temperature, temperature, MAX_TEMP_LEN);
    data->temperature[MAX_TEMP_LEN - 1] = '\0';
}

const char* getWeekDay(const WeatherData* data){
    return data->weekDay;
}

void setWeekDay(WeatherData* data, const char* weekDay){
    strncpy(data->weekDay, weekDay, MAX_WEEKDAY_LEN);
    data->weekDay[MAX_WEEKDAY_LEN - 1] = '\0';
}

bool getLoadData(const WeatherData* data) {
    return data->loadData;
}

void setLoadData(WeatherData* data, bool loadData) {
    data->loadData = loadData;
}

const char* getDate(const WeatherData* data){
    return data->date;
}

void setDate(WeatherData* data, const char* date){
    strncpy(data->date, date, MAX_DATE_LEN);
    data->date[MAX_DATE_LEN - 1] = '\0';
}

const char* getPrognosImage(const WeatherData* data){
    return data->prognosImage;
}

void setPrognosImage(WeatherData* data, const char* prognosImage){
    strncpy(data->prognosImage, prognosImage, MAX_IMAGE_LEN);
    data->prognosImage[MAX_IMAGE_LEN - 1] = '\0';
}

void freeWeatherObject(WeatherData* obj) {
    free(obj);
}

// WeatherList som tar emot Weather
WeatherList* createWeatherList(const char* city_name, int capacity) {
    WeatherList* list = malloc(sizeof(WeatherList));
    list->data = malloc(sizeof(WeatherData) * capacity);
    list->size = 0;
    list->capacity = capacity;
    strcpy(list->city_name, city_name);
    list->city_name[MAX_CITY_NAME_LEN - 1] = '\0';
    return list;
}

const char* getCityName(const WeatherList* list) {
    return list->city_name;
}

void setCityName(WeatherList* list, const char* cityName) {
    strncpy(list->city_name, cityName, MAX_CITY_NAME_LEN);
    list->city_name[MAX_CITY_NAME_LEN - 1] = '\0';
}

void addWeatherData(WeatherList* list, WeatherData* data) {
    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->data = realloc(list->data, sizeof(WeatherData) * list->capacity);
    }
    list->data[list->size++] = *data;
}

WeatherData* getWeatherData(const WeatherList* list, int index) {
    if (index < 0 || index >= list->size) {
        return NULL;
    }
    return &list->data[index];
}

int getWeatherListSize(const WeatherList* list) {
    return list->size;
}

void freeWeatherList(WeatherList* list) {
    free(list->data);
    free(list);
}




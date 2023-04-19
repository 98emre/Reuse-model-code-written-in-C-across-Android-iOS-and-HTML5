// Importera modellen
#include "Model.h"

// En enkel funktion som skriver ut "Hello World From C" till konsolen
void testFunc(void){
    printf("Hello World From C");
}

// En funktion som kopierar en inmatad sträng till en ny minnesplats och returnerar en pekare till den nya strängen
char *getText(const char* input_str){
    char *result = malloc(strlen(input_str));
    strcpy(result, input_str);
    return result;
}

// En funktion som skapar en ny instans av structen "WeatherData" med hjälp av de inmatade parametrarna
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

// En funktion som returnerar stadens namn från en "WeatherData" instans
const char* getCityName(const WeatherData* data) {
    return data->city_name;
}

// En funktion som sätter stadens namn för en "WeatherData" instans
void setCityName(WeatherData* data, const char* cityName) {
    strncpy(data->city_name, cityName, MAX_CITY_NAME_LEN);
    data->city_name[MAX_CITY_NAME_LEN - 1] = '\0';
}

// En funktion som returnerar temperaturen från en "WeatherData" instans
const char* getTemperature(const WeatherData* data) {
    return data->temperature;
}

// En funktion som sätter temperaturen för en "WeatherData" instans
void setTemperature(WeatherData* data, const char* temperature) {
    strncpy(data->temperature, temperature, MAX_TEMP_LEN);
    data->temperature[MAX_TEMP_LEN - 1] = '\0';
}

// En funktion som returnerar veckodagen från en "WeatherData" instans
const char* getWeekDay(const WeatherData* data){
    return data->weekDay;
}

// En funktion som sätter veckodagen för en "WeatherData" instans
void setWeekDay(WeatherData* data, const char* weekDay){
    strncpy(data->weekDay, weekDay, MAX_WEEKDAY_LEN);
    data->weekDay[MAX_WEEKDAY_LEN - 1] = '\0';
}

// En funktion som returnerar om det finns data för en "WeatherData" instans
bool getLoadData(const WeatherData* data) {
    return data->loadData;
}


// Funktion som sätter en boolean i en WeatherData-objekt
void setLoadData(WeatherData* data, bool loadData) {
    data->loadData = loadData;
}

// Funktion som hämtar datumet från en WeatherData-objekt
const char* getDate(const WeatherData* data){
    return data->date;
}

// Funktion som sätter datumet i en WeatherData-objekt
void setDate(WeatherData* data, const char* date){
    strncpy(data->date, date, MAX_DATE_LEN);
    data->date[MAX_DATE_LEN - 1] = '\0';
}

// Funktion som hämtar prognosbilden från en WeatherData-objekt
const char* getPrognosImage(const WeatherData* data){
    return data->prognosImage;
}

// Funktion som sätter prognosbilden i en WeatherData-objekt
void setPrognosImage(WeatherData* data, const char* prognosImage){
    strncpy(data->prognosImage, prognosImage, MAX_IMAGE_LEN);
    data->prognosImage[MAX_IMAGE_LEN - 1] = '\0';
}

// Funktion som frigör minnet som allokerats för en WeatherData-objekt
void freeWeatherObject(WeatherData* obj) {
    free(obj);
}





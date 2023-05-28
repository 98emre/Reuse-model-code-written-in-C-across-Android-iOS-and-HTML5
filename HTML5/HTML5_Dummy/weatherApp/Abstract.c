
    
    #include "Model.h"
    #include <emscripten.h>

    EMSCRIPTEN_KEEPALIVE
    WeatherData* createWeatherObjectFromCWrapper(const char* approvedTime) {
        return createWeatherObjectFromC(approvedTime);
    }

    EMSCRIPTEN_KEEPALIVE
    const char* getApprovedTimeWrapper(const WeatherData* data) {
        return getApprovedTime(data);
    }

    EMSCRIPTEN_KEEPALIVE
    void setApprovedTimeWrapper(WeatherData* data, const char* approvedTime) {
        setApprovedTime(data, approvedTime);
    }

    
    EMSCRIPTEN_KEEPALIVE
    HourlyWeatherData* getHourlyDataWrapper(const WeatherData* data, int index) {
        return getHourlyData(data, index);
    }


    EMSCRIPTEN_KEEPALIVE
    void addHourlyDataWrapper(WeatherData* data, HourlyWeatherData* hourlyData) {
        addHourlyData(data, hourlyData);
    }

    EMSCRIPTEN_KEEPALIVE
    int getHourlyDataSizeWrapper(const WeatherData* data) {
        return getHourlyDataSize(data);
    }

    EMSCRIPTEN_KEEPALIVE
    float getLatWrapper(const WeatherData* data) {
        return getLat(data);
    }

    EMSCRIPTEN_KEEPALIVE
    void setLatWrapper(WeatherData* data, float lat) {
        setLat(data, lat);
    }

    EMSCRIPTEN_KEEPALIVE
    float getLonWrapper(const WeatherData* data) {
        return getLon(data);
    }

    EMSCRIPTEN_KEEPALIVE
    void setLonWrapper(WeatherData* data, float lon) {
        setLon(data, lon);
    }

    EMSCRIPTEN_KEEPALIVE
    void freeWeatherObjectWrapper(WeatherData* obj) {
        freeWeatherObject(obj);
    }

    EMSCRIPTEN_KEEPALIVE
    HourlyWeatherData* createHourlyWeatherObjectFromCWrapper(const char* time, const char* temperature, const char* icon) {
        return createHourlyWeatherObjectFromC(time, temperature, icon);
    }

    EMSCRIPTEN_KEEPALIVE
    const char* getTimeWrapper(const HourlyWeatherData* data) {
        return getTime(data);
    }

    EMSCRIPTEN_KEEPALIVE
    void setTimeWrapper(HourlyWeatherData* data, const char* time) {
        setTime(data, time);
    }

    EMSCRIPTEN_KEEPALIVE
    const char* getTemperatureWrapper(const HourlyWeatherData* data) {
        return getTemperature(data);
    }

    EMSCRIPTEN_KEEPALIVE
    void setTemperatureWrapper(HourlyWeatherData* data, const char* temperature) {
        setTemperature(data, temperature);
    }

    EMSCRIPTEN_KEEPALIVE
    const char* getIconWrapper(const HourlyWeatherData* data) {
        return getIcon(data);
    }

    EMSCRIPTEN_KEEPALIVE
    void setIconWrapper(HourlyWeatherData* data, const char* icon) {
        setIcon(data, icon);
    }

    EMSCRIPTEN_KEEPALIVE
    void freeHourlyWeatherObjectWrapper(HourlyWeatherData* obj) {
        freeHourlyWeatherObject(obj);
    }

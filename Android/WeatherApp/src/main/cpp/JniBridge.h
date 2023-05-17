#include "jni.h"
#include "Model.h"


JNIEXPORT jobject JNICALL Java_com_example_weatherapp_WeatherNative_createWeatherObjectFromC(JNIEnv *env, jobject obj, jstring approvedTime);
JNIEXPORT jdouble JNICALL Java_com_example_weatherapp_WeatherNative_getLat(JNIEnv *env, jobject obj, jobject weatherDataObj);
JNIEXPORT void JNICALL Java_com_example_weatherapp_WeatherNative_setLat(JNIEnv *env, jobject obj, jobject weatherDataObj, jdouble lat);
JNIEXPORT jdouble JNICALL Java_com_example_weatherapp_WeatherNative_getLon(JNIEnv *env, jobject obj, jobject weatherDataObj);
JNIEXPORT void JNICALL Java_com_example_weatherapp_WeatherNative_setLon(JNIEnv *env, jobject obj, jobject weatherDataObj, jdouble lon);
JNIEXPORT jstring JNICALL Java_com_example_weatherapp_WeatherNative_getApprovedTime(JNIEnv *env, jobject obj, jobject weatherDataObj);
JNIEXPORT void JNICALL Java_com_example_weatherapp_WeatherNative_setApprovedTime(JNIEnv *env, jobject obj, jobject weatherDataObj, jstring approvedTime);
JNIEXPORT jint JNICALL Java_com_example_weatherapp_WeatherNative_getHourlyDataSize(JNIEnv *env, jobject obj, jobject weatherDataObj);
JNIEXPORT jstring JNICALL Java_com_example_weatherapp_WeatherNative_getTime(JNIEnv *env, jobject obj, jobject hourlyDataObj);
JNIEXPORT void JNICALL Java_com_example_weatherapp_WeatherNative_setTime(JNIEnv *env, jobject obj, jobject hourlyDataObj, jstring time);
JNIEXPORT jstring JNICALL Java_com_example_weatherapp_WeatherNative_getTemperature(JNIEnv *env, jobject obj, jobject hourlyDataObj);
JNIEXPORT void JNICALL Java_com_example_weatherapp_WeatherNative_setTemperature(JNIEnv *env, jobject obj, jobject hourlyDataObj, jstring temperature);
JNIEXPORT jstring JNICALL Java_com_example_weatherapp_WeatherNative_getIcon(JNIEnv *env, jobject obj, jobject hourlyDataObj);
JNIEXPORT void JNICALL Java_com_example_weatherapp_WeatherNative_setIcon(JNIEnv *env, jobject obj, jobject hourlyDataObj, jstring icon);
JNIEXPORT jobject JNICALL Java_com_example_weatherapp_WeatherNative_createHourlyWeatherObjectFromC(JNIEnv *env, jobject obj, jstring time, jstring temperature, jstring icon);
JNIEXPORT jobject JNICALL Java_com_example_weatherapp_WeatherNative_getHourlyData(JNIEnv *env, jobject obj, jobject weatherDataObj, jint index);
JNIEXPORT void JNICALL Java_com_example_weatherapp_WeatherNative_addHourlyData(JNIEnv *env, jobject thisObj, jobject dataObj, jobject hourlyDataObj);
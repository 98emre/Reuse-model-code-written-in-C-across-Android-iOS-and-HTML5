#include "jni.h"

// Funktion för att skapa ett WeatherDataNative objekt i C från Java-objekt
JNIEXPORT jobject JNICALL Java_com_example_weatherapp_WeatherDataNative_createWeatherObjectFromC
(JNIEnv *env, jobject this,
                                    jstring city_name,
                                    jstring temperature,
                                    jstring weekDay,
                                    jboolean loadData,
                                    jstring date,
                                    jstring prognosImage);

// Funktion för att hämta city_name fältet från ett WeatherDataNative Kotlin objekt
JNIEXPORT jstring JNICALL Java_com_example_weatherapp_WeatherDataNative_getCityName
(JNIEnv *env, jobject this, jobject data);

// Funktion för att ändra city_name fältet i ett WeatherDataNative Kotlin objekt
JNIEXPORT void JNICALL Java_com_example_weatherapp_WeatherDataNative_setCityName
(JNIEnv *env, jobject this, jobject data, jstring city);

// Funktion för att hämta city_name temperature från ett WeatherDataNative Kotlin objekt
JNIEXPORT jstring JNICALL Java_com_example_weatherapp_WeatherDataNative_getTemperature
(JNIEnv *env, jobject this, jobject data);

// Funktion för att ändra temperature fältet i ett WeatherDataNative Kotlin objekt
JNIEXPORT void JNICALL Java_com_example_weatherapp_WeatherDataNative_setTemperature
        (JNIEnv *env, jobject this, jobject data, jstring weekDay);

// Funktion för att hämta weekDay fältet från ett WeatherDataNative Kotlin objekt
JNIEXPORT jstring JNICALL Java_com_example_weatherapp_WeatherDataNative_getWeekDay
        (JNIEnv *env, jobject this, jobject data);

// Funktion för att ändra weekDay fältet i ett WeatherDataNative Kotlin objekt
JNIEXPORT void JNICALL Java_com_example_weatherapp_WeatherDataNative_setWeekDay
        (JNIEnv *env, jobject this, jobject data, jstring weekDay);

// Funktion för att hämta loadData fältet från ett WeatherDataNative Kotlin objekt
JNIEXPORT jboolean JNICALL Java_com_example_weatherapp_WeatherDataNative_getLoadData
        (JNIEnv *env, jobject this, jobject data);

// Funktion för att ändra loadData fältet i ett WeatherDataNative Kotlin objekt
JNIEXPORT void JNICALL Java_com_example_weatherapp_WeatherDataNative_setLoadData
        (JNIEnv *env, jobject this, jobject data, jboolean loadData);

// Funktion för att hämta date fältet från ett WeatherDataNative Kotlin objekt
JNIEXPORT jstring JNICALL Java_com_example_weatherapp_WeatherDataNative_getDate
        (JNIEnv *env, jobject this, jobject data);

// Funktion för att ändra date fältet i ett WeatherDataNative Kotlin objekt
JNIEXPORT void JNICALL Java_com_example_weatherapp_WeatherDataNative_setDate
        (JNIEnv *env, jobject this, jobject data, jstring date);

// Funktion för att hämta prognosImage fältet från ett WeatherDataNative Kotlin objekt
JNIEXPORT jstring JNICALL Java_com_example_weatherapp_WeatherDataNative_getPrognosImage
        (JNIEnv *env, jobject this, jobject data);

// Funktion för att ändra prognosImage fältet i ett WeatherDataNative Kotlin objekt
JNIEXPORT void JNICALL Java_com_example_weatherapp_WeatherDataNative_setPrognosImage
        (JNIEnv *env, jobject this, jobject data, jstring prognosImage);

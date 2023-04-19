#include "jni.h"
#include <stdlib.h>
#include <string.h>
#include "weather.h"
#include "JniBridge.h"

// Funktion för att skapa ett WeatherDataNative Kotlin objekt från C kod
JNIEXPORT jobject JNICALL
Java_com_example_weatherapp_WeatherDataNative_createWeatherObjectFromC(JNIEnv *env,
                                                                      jobject this,
                                                                      jstring city_name,
                                                                      jstring temperature,
                                                                      jstring weekDay,
                                                                      jboolean loadData,
                                                                      jstring date,
                                                                      jstring prognosImage) {

    // Hämta strängarna från Kotlin Objektet
    const char *c_city_name = (*env)->GetStringUTFChars(env, city_name, NULL);
    const char *c_temperature = (*env)->GetStringUTFChars(env, temperature, NULL);
    const char *c_weekDay = (*env)->GetStringUTFChars(env, weekDay, NULL);
    const char *c_date = (*env)->GetStringUTFChars(env, date, NULL);
    const char *c_prognosImage = (*env)->GetStringUTFChars(env, prognosImage, NULL);


    // Skapa ett WeatherData Objekt från C filen ( weather.c )
    WeatherData *data_ptr = createWeatherObjectFromC(
            c_city_name,
            c_temperature,
            c_weekDay,
            loadData,
            c_date,
            c_prognosImage);

    WeatherData data = *data_ptr;

    // Skapa ett Kotlin Objekt av klassen WeatherDataNative
    jclass weatherClass = (*env)->FindClass(env, "com/example/weatherapp/WeatherDataNative");
    jobject weatherObject = (*env)->AllocObject(env, weatherClass);

    // Sätt fältvärdena / variabler för java objektet ( WeatherDataNative )
    (*env)->SetObjectField(env, weatherObject,
                           (*env)->GetFieldID(env, weatherClass, "city_name", "Ljava/lang/String;"),
                           (*env)->NewStringUTF(env, data.city_name));

    (*env)->SetObjectField(env, weatherObject,
                           (*env)->GetFieldID(env, weatherClass, "temperature", "Ljava/lang/String;"),
                           (*env)->NewStringUTF(env, data.temperature));

    (*env)->SetObjectField(env, weatherObject,
                           (*env)->GetFieldID(env, weatherClass, "weekDay", "Ljava/lang/String;"),
                           (*env)->NewStringUTF(env, data.weekDay));

    (*env)->SetBooleanField(env, weatherObject,
                            (*env)->GetFieldID(env, weatherClass, "loadData", "Z"),
                            (jboolean) data.loadData);

    (*env)->SetObjectField(env, weatherObject,
                           (*env)->GetFieldID(env, weatherClass, "date", "Ljava/lang/String;"),
                           (*env)->NewStringUTF(env, data.date));

    (*env)->SetObjectField(env, weatherObject,
                           (*env)->GetFieldID(env, weatherClass, "prognosImage", "Ljava/lang/String;"),
                           (*env)->NewStringUTF(env, data.prognosImage));


    freeWeatherObject(data_ptr);

    // Frigör minnet för strängarna (C variabler)
    (*env)->ReleaseStringUTFChars(env, city_name, c_city_name);
    (*env)->ReleaseStringUTFChars(env, temperature, c_temperature);
    (*env)->ReleaseStringUTFChars(env, weekDay, c_weekDay);
    (*env)->ReleaseStringUTFChars(env, date, c_date);
    (*env)->ReleaseStringUTFChars(env, prognosImage, c_prognosImage);

    // Returnera Java-objektet
    return weatherObject;
}

// Funktioner för att hämta och sätta värdena för WeatherDataNative Kotlin objektet

// 1. GetObjectClass används för att hämta klassen för Kotlin objektet data.
// 2. GetFieldID används för att hämta fält ID för fältet variabel i klassen.
// 3. GetObjectField används för att hämta värdet för fältet med hjälp av fält ID.
// 4. SetObjectField används för att ange värdet för fältet med hjälp av fält ID och det nya värdet

// Funktion för att hämta city_name fältet i ett WeatherDataNative Kotlin objekt
JNIEXPORT jstring JNICALL
Java_com_example_weatherapp_WeatherDataNative_getCityName(JNIEnv *env, jobject this, jobject data) {
    // Hämta klassen för  WeatherDataNative objektet
    jclass class = (*env)->GetObjectClass(env, data);
    // Hämta fält ID för city_name fältet i klassen
    jfieldID field = (*env)->GetFieldID(env, class, "city_name", "Ljava/lang/String;");
    // Hämta värdet av city_name fältet för det givna objektet
    jstring city = (*env)->GetObjectField(env, data, field);
    // Returnera city_name som en jstring
    return city;
}

// Funktion för att ändra city_name fältet från i ett WeatherDataNative Kotlin objekt
JNIEXPORT void JNICALL
Java_com_example_weatherapp_WeatherDataNative_setCityName(JNIEnv *env, jobject this, jobject data, jstring city) {
    // Hämta klassen för  WeatherDataNative objektet
    jclass class = (*env)->GetObjectClass(env, data);
    // Hämta fält ID för city_name fältet i klassen
    jfieldID field = (*env)->GetFieldID(env, class, "city_name", "Ljava/lang/String;");
    // Ändra värdet av city_name fältet för det givna objektet till det nya värdet
    (*env)->SetObjectField(env, data, field, city);
}

// Funktion för att hämta temperature fältet i ett WeatherDataNative Kotlin objekt
JNIEXPORT jstring JNICALL
Java_com_example_weatherapp_WeatherDataNative_getTemperature(JNIEnv *env, jobject this, jobject data) {
    // Hämta klassen för  WeatherDataNative objektet
    jclass class = (*env)->GetObjectClass(env, data);
    // Hämta fält ID för temperature fältet i klassen
    jfieldID field = (*env)->GetFieldID(env, class, "temperature", "Ljava/lang/String;");
    // Hämta värdet av temperature fältet för det givna objektet
    jstring temperature = (*env)->GetObjectField(env, data, field);
    return temperature;
}

// Funktion för att ändra temperature fältet från i ett WeatherDataNative Kotlin objekt
JNIEXPORT void JNICALL
Java_com_example_weatherapp_WeatherDataNative_setTemperature(JNIEnv *env, jobject this, jobject data, jstring temperature) {
    // Hämta klassen för  WeatherDataNative objektet
    jclass class = (*env)->GetObjectClass(env, data);
    // Hämta fält ID för temperature fältet i klassen
    jfieldID field = (*env)->GetFieldID(env, class, "temperature", "Ljava/lang/String;");
    // Ändra värdet av temperature fältet för det givna objektet till det nya värdet
    (*env)->SetObjectField(env, data, field, temperature);
}

// Funktion för att hämta weekDay fältet i ett WeatherDataNative Kotlin objekt
JNIEXPORT jstring JNICALL
Java_com_example_weatherapp_WeatherDataNative_getWeekDay(JNIEnv *env, jobject this, jobject data) {
    // Hämta klassen för  WeatherDataNative objektet
    jclass class = (*env)->GetObjectClass(env, data);
    // Hämta fält ID för weekday fältet i klassen
    jfieldID field = (*env)->GetFieldID(env, class, "weekDay", "Ljava/lang/String;");
    // Hämta värdet av weekDay fältet för det givna objektet
    jstring weekDay = (*env)->GetObjectField(env, data, field);
    // Returnera weekDay som en jstring
    return weekDay;
}

// Funktion för att ändra weekday fältet från i ett WeatherDataNative Kotlin objekt
JNIEXPORT void JNICALL
Java_com_example_weatherapp_WeatherDataNative_setWeekDay(JNIEnv *env, jobject this, jobject data, jstring weekDay) {
    // Hämta klassen för  WeatherDataNative objektet
    jclass class = (*env)->GetObjectClass(env, data);
    // Hämta fält ID för weekday fältet i klassen
    jfieldID field = (*env)->GetFieldID(env, class, "weekDay", "Ljava/lang/String;");
    // Ändra värdet av weekDay fältet för det givna objektet till det nya värdet
    (*env)->SetObjectField(env, data, field, weekDay);
}

// Funktion för att hämta loadData fältet i ett WeatherDataNative Kotlin objekt
JNIEXPORT jboolean JNICALL
Java_com_example_weatherapp_WeatherDataNative_getLoadData(JNIEnv *env, jobject this, jobject data) {
    // Hämta klassen för  WeatherDataNative objektet
    jclass class = (*env)->GetObjectClass(env, data);
    // Hämta fält ID för loadData fältet i klassen
    jfieldID field = (*env)->GetFieldID(env, class, "loadData", "Z");
    // Hämta värdet av loadData fältet för det givna objektet
    jboolean loadData = (*env)->GetBooleanField(env, data, field);
    // Returnera loadData som en jstring
    return loadData;
}

// Funktion för att ändra loadData fältet från i ett WeatherDataNative Kotlin objekt
JNIEXPORT void JNICALL
Java_com_example_weatherapp_WeatherDataNative_setLoadData(JNIEnv *env, jobject this, jobject data, jboolean loadData) {
    // Hämta klassen för  WeatherDataNative objektet
    jclass class = (*env)->GetObjectClass(env, data);
    // Hämta fält ID för loadData fältet i klassen
    jfieldID field = (*env)->GetFieldID(env, class, "loadData", "Z");
    // Ändra värdet av loadData fältet för det givna objektet till det nya värdet
    (*env)->SetBooleanField(env, data, field, loadData);
}

// Funktion för att hämta date fältet i ett WeatherDataNative Kotlin objekt
JNIEXPORT jstring JNICALL
Java_com_example_weatherapp_WeatherDataNative_getDate(JNIEnv *env, jobject this, jobject data) {
    // Hämta klassen för  WeatherDataNative objektet
    jclass class = (*env)->GetObjectClass(env, data);
    // Hämta fält ID för date fältet i klassen
    jfieldID field = (*env)->GetFieldID(env, class, "date", "Ljava/lang/String;");
    // Hämta värdet av date fältet för det givna objektet
    jstring date = (*env)->GetObjectField(env, data, field);
    // Returnera date som en jstring
    return date;
}

// Funktion för att ändra date fältet från i ett WeatherDataNative Kotlin objekt
JNIEXPORT void JNICALL
Java_com_example_weatherapp_WeatherDataNative_setDate(JNIEnv *env, jobject this, jobject data, jstring date) {
    // Hämta klassen för  WeatherDataNative objektet
    jclass class = (*env)->GetObjectClass(env, data);
    // Hämta fält ID för date fältet i klassen
    jfieldID field = (*env)->GetFieldID(env, class, "date", "Ljava/lang/String;");
    // Ändra värdet av date fältet för det givna objektet till det nya värdet
    (*env)->SetObjectField(env, data, field, date);
}


// Funktion för att hämta prognosImage fältet i ett WeatherDataNative Kotlin objekt
JNIEXPORT jstring JNICALL
Java_com_example_weatherapp_WeatherDataNative_getPrognosImage(JNIEnv *env, jobject this, jobject data) {
    // Hämta klassen för  WeatherDataNative objektet
    jclass class = (*env)->GetObjectClass(env, data);
    // Hämta fält ID för prognosImage fältet i klassen
    jfieldID field = (*env)->GetFieldID(env, class, "prognosImage", "Ljava/lang/String;");
    // Hämta värdet av prognosImage fältet för det givna objektet
    jstring prognosImage = (*env)->GetObjectField(env, data, field);
    // Returnera prognosImage som en jstring
    return prognosImage;
}

// Funktion för att ändra prognosImage fältet från i ett WeatherDataNative Kotlin objekt
JNIEXPORT void JNICALL
Java_com_example_weatherapp_WeatherDataNative_setPrognosImage(JNIEnv *env, jobject this,jobject data, jstring prognosImage) {
    // Hämta klassen för  WeatherDataNative objektet
    jclass class = (*env)->GetObjectClass(env, data);
    // Hämta fält ID för prognosImage fältet i klassen
    jfieldID field = (*env)->GetFieldID(env, class, "prognosImage", "Ljava/lang/String;");
    // Ändra värdet av prognosImage fältet för det givna objektet till det nya värdet
    (*env)->SetObjectField(env, data, field, prognosImage);
}



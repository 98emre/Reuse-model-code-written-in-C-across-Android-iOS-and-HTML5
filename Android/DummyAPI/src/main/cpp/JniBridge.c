#include "jni.h"
#include <stdlib.h>
#include <string.h>
#include "Model.h"
#include "JniBridge.h"

JNIEXPORT jobject JNICALL Java_com_example_weatherapp_WeatherNative_createWeatherObjectFromC(JNIEnv *env, jobject obj, jstring approvedTime) {
    // Hämta strängen från Kotlin-objektet
    const char *c_approvedTime = (*env)->GetStringUTFChars(env, approvedTime, NULL);

    // Skapa ett WeatherNative-objekt från C-filen
    WeatherData *weatherNative = createWeatherObjectFromC( c_approvedTime);

    // Skapa ett Kotlin-objekt av klassen WeatherNative
    jclass weatherNativeClass = (*env)->FindClass(env, "com/example/weatherapp/WeatherNative");
    jmethodID weatherNativeConstructor = (*env)->GetMethodID(env, weatherNativeClass, "<init>", "()V");
    jobject weatherNativeObject = (*env)->NewObject(env, weatherNativeClass, weatherNativeConstructor);

    // Sätt fältvärdena / variabler för Java-objektet
    jfieldID approvedTimeField = (*env)->GetFieldID(env, weatherNativeClass, "approvedTime", "Ljava/lang/String;");
    jstring approvedTimeString = (*env)->NewStringUTF(env, weatherNative->approvedTime);
    (*env)->SetObjectField(env, weatherNativeObject, approvedTimeField, approvedTimeString);

    jfieldID sizeField = (*env)->GetFieldID(env, weatherNativeClass, "size", "I");
    (*env)->SetIntField(env, weatherNativeObject, sizeField, weatherNative->size);

    jfieldID dataField = (*env)->GetFieldID(env, weatherNativeClass, "data", "Ljava/util/List;");
    jobject dataList = (*env)->GetObjectField(env, weatherNativeObject, dataField);

    // Sätt fältvärdena för listan av HourlyWeatherData-objekt
    jclass hourlyWeatherDataClass = (*env)->FindClass(env, "com/example/weatherapp/WeatherNative$HourlyWeatherData");
    jmethodID hourlyWeatherDataConstructor = (*env)->GetMethodID(env, hourlyWeatherDataClass, "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");

    for (int i = 0; i < weatherNative->size; i++) {
        HourlyWeatherData* hourlyData = getHourlyData(weatherNative, i);

        jstring timeString = (*env)->NewStringUTF(env, hourlyData->time);
        jstring temperatureString = (*env)->NewStringUTF(env, hourlyData->temperature);
        jstring iconString = (*env)->NewStringUTF(env, hourlyData->icon);

        jobject hourlyWeatherDataObject = (*env)->NewObject(env, hourlyWeatherDataClass, hourlyWeatherDataConstructor, timeString, temperatureString, iconString);

        jmethodID addMethod = (*env)->GetMethodID(env, (*env)->GetObjectClass(env, dataList), "add", "(Ljava/lang/Object;)Z");
        (*env)->CallBooleanMethod(env, dataList, addMethod, hourlyWeatherDataObject);

        // Rensa minne för strängarna och hourlyData-objektet
        (*env)->ReleaseStringUTFChars(env, timeString, hourlyData->time);
        (*env)->ReleaseStringUTFChars(env, temperatureString, hourlyData->temperature);
        (*env)->ReleaseStringUTFChars(env, iconString, hourlyData->icon);

        // Rensa upp referenser
        (*env)->DeleteLocalRef(env, hourlyWeatherDataObject);
        (*env)->DeleteLocalRef(env, timeString);
        (*env)->DeleteLocalRef(env, temperatureString);
        (*env)->DeleteLocalRef(env, iconString);

        // Använd freeHourlyData funktionen här
        freeHourlyWeatherObject(hourlyData);

        // Rensa upp referenser
        (*env)->DeleteLocalRef(env, hourlyWeatherDataObject);

        //free(hourlyData);
    }

    // Rensa minne för weatherNative-objektet
    freeWeatherObject(weatherNative);

    // Rensa minne för strängen
    (*env)->ReleaseStringUTFChars(env, approvedTime, c_approvedTime);

    // Returnera Java-objektet
    return weatherNativeObject;

}

JNIEXPORT jdouble JNICALL Java_com_example_weatherapp_WeatherNative_getLat(JNIEnv *env, jobject obj, jobject weatherDataObj) {
    // Get the value of the lat field from the WeatherData object
    jclass weatherDataClass = (*env)->GetObjectClass(env, weatherDataObj);
    jfieldID latField = (*env)->GetFieldID(env, weatherDataClass, "lat", "F");
    jfloat lat = (*env)->GetFloatField(env, weatherDataObj, latField);

    return lat;
}

JNIEXPORT void JNICALL Java_com_example_weatherapp_WeatherNative_setLat(JNIEnv *env, jobject obj, jobject weatherDataObj, jdouble lat) {
    // Set the value of the lat field in the WeatherData object
    jclass weatherDataClass = (*env)->GetObjectClass(env, weatherDataObj);
    jfieldID latField = (*env)->GetFieldID(env, weatherDataClass, "lat", "F");
    (*env)->SetFloatField(env, weatherDataObj, latField, lat);
}

JNIEXPORT jdouble JNICALL Java_com_example_weatherapp_WeatherNative_getLon(JNIEnv *env, jobject obj, jobject weatherDataObj) {
    // Get the value of the lon field from the WeatherData object
    jclass weatherDataClass = (*env)->GetObjectClass(env, weatherDataObj);
    jfieldID lonField = (*env)->GetFieldID(env, weatherDataClass, "lon", "F");
    jfloat lon = (*env)->GetFloatField(env, weatherDataObj, lonField);

    return lon;
}

JNIEXPORT void JNICALL Java_com_example_weatherapp_WeatherNative_setLon(JNIEnv *env, jobject obj, jobject weatherDataObj, jdouble lon) {
    // Set the value of the lon field in the WeatherData object
    jclass weatherDataClass = (*env)->GetObjectClass(env, weatherDataObj);
    jfieldID lonField = (*env)->GetFieldID(env, weatherDataClass, "lon", "F");
    (*env)->SetFloatField(env, weatherDataObj, lonField, lon);
}


JNIEXPORT jstring JNICALL Java_com_example_weatherapp_WeatherNative_getApprovedTime(JNIEnv *env, jobject obj, jobject weatherDataObj) {
    // Get the value of the approvedTime field from the WeatherData object
    jclass weatherDataClass = (*env)->GetObjectClass(env, weatherDataObj);
    jfieldID approvedTimeField = (*env)->GetFieldID(env, weatherDataClass, "approvedTime", "Ljava/lang/String;");
    jstring approvedTime = (jstring) (*env)->GetObjectField(env, weatherDataObj, approvedTimeField);

    return approvedTime;
}

JNIEXPORT void JNICALL Java_com_example_weatherapp_WeatherNative_setApprovedTime(JNIEnv *env, jobject obj, jobject weatherDataObj, jstring approvedTime) {
    // Set the value of the approvedTime field in the WeatherData object
    jclass weatherDataClass = (*env)->GetObjectClass(env, weatherDataObj);
    jfieldID approvedTimeField = (*env)->GetFieldID(env, weatherDataClass, "approvedTime", "Ljava/lang/String;");
    (*env)->SetObjectField(env, weatherDataObj, approvedTimeField, approvedTime);
}

JNIEXPORT jint JNICALL Java_com_example_weatherapp_WeatherNative_getHourlyDataSize(JNIEnv *env, jobject obj, jobject weatherDataObj) {
    // Get the size of the WeatherData object's list of data
    jclass weatherDataClass = (*env)->GetObjectClass(env, weatherDataObj);
    jfieldID dataField = (*env)->GetFieldID(env, weatherDataClass, "data", "Ljava/util/List;");
    jobject dataListObj = (*env)->GetObjectField(env, weatherDataObj, dataField);
    jclass dataListClass = (*env)->GetObjectClass(env, dataListObj);
    jmethodID toArrayMethod = (*env)->GetMethodID(env, dataListClass, "toArray", "()[Ljava/lang/Object;");
    jobjectArray dataArray = (jobjectArray) (*env)->CallObjectMethod(env, dataListObj, toArrayMethod);

    // Check if dataArray is null or not of expected type
    if (dataArray == NULL) {
        return 0;
    }
    jsize dataSize = (*env)->GetArrayLength(env, dataArray);
    return dataSize;
}

JNIEXPORT jstring JNICALL Java_com_example_weatherapp_WeatherNative_getTime(JNIEnv *env, jobject obj, jobject hourlyDataObj) {
    // Get the value of the time field from the HourlyWeatherData object
    jclass hourlyDataClass = (*env)->GetObjectClass(env, hourlyDataObj);
    jfieldID timeField = (*env)->GetFieldID(env, hourlyDataClass, "time", "Ljava/lang/String;");
    jstring time = (jstring) (*env)->GetObjectField(env, hourlyDataObj, timeField);

    return time;
}

JNIEXPORT void JNICALL Java_com_example_weatherapp_WeatherNative_setTime(JNIEnv *env, jobject obj, jobject hourlyDataObj, jstring time) {
    // Set the value of the time field in the HourlyWeatherData object
    jclass hourlyDataClass = (*env)->GetObjectClass(env, hourlyDataObj);
    jfieldID timeField = (*env)->GetFieldID(env, hourlyDataClass, "time", "Ljava/lang/String;");
    (*env)->SetObjectField(env, hourlyDataObj, timeField, time);
}

JNIEXPORT jstring JNICALL Java_com_example_weatherapp_WeatherNative_getTemperature(JNIEnv *env, jobject obj, jobject hourlyDataObj) {
    // Get the value of the temperature field from the HourlyWeatherData object
    jclass hourlyDataClass = (*env)->GetObjectClass(env, hourlyDataObj);
    jfieldID temperatureField = (*env)->GetFieldID(env, hourlyDataClass, "temperature", "Ljava/lang/String;");
    jstring temperature = (jstring) (*env)->GetObjectField(env, hourlyDataObj, temperatureField);

    return temperature;
}

JNIEXPORT void JNICALL Java_com_example_weatherapp_WeatherNative_setTemperature(JNIEnv *env, jobject obj, jobject hourlyDataObj, jstring temperature) {
    // Set the value of the temperature field in the HourlyWeatherData object
    jclass hourlyDataClass = (*env)->GetObjectClass(env, hourlyDataObj);
    jfieldID temperatureField = (*env)->GetFieldID(env, hourlyDataClass, "temperature", "Ljava/lang/String;");
    (*env)->SetObjectField(env, hourlyDataObj, temperatureField, temperature);
}

JNIEXPORT jstring JNICALL Java_com_example_weatherapp_WeatherNative_getIcon(JNIEnv *env, jobject obj, jobject hourlyDataObj) {
    // Get the value of the icon field from the HourlyWeatherData object
    jclass hourlyDataClass = (*env)->GetObjectClass(env, hourlyDataObj);
    jfieldID iconField = (*env)->GetFieldID(env, hourlyDataClass, "icon", "Ljava/lang/String;");
    jstring icon = (jstring) (*env)->GetObjectField(env, hourlyDataObj, iconField);

    return icon;
}

JNIEXPORT void JNICALL Java_com_example_weatherapp_WeatherNative_setIcon(JNIEnv *env, jobject obj, jobject hourlyDataObj, jstring icon) {
    // Set the value of the icon field in the HourlyWeatherData object
    jclass hourlyDataClass = (*env)->GetObjectClass(env, hourlyDataObj);
    jfieldID iconField = (*env)->GetFieldID(env, hourlyDataClass, "icon", "Ljava/lang/String;");
    (*env)->SetObjectField(env, hourlyDataObj, iconField, icon);
}

JNIEXPORT jobject JNICALL Java_com_example_weatherapp_WeatherNative_createHourlyWeatherObjectFromC(JNIEnv *env, jobject obj, jstring time, jstring temperature, jstring icon) {
    // Create a new HourlyWeatherData object
    jclass hourlyDataClass = (*env)->FindClass(env, "com/example/weatherapp/WeatherNative$HourlyWeatherData");
    jmethodID constructor = (*env)->GetMethodID(env, hourlyDataClass, "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
    jobject hourlyDataObj = (*env)->NewObject(env, hourlyDataClass, constructor, time, temperature, icon);

    return hourlyDataObj;
}

JNIEXPORT jobject JNICALL Java_com_example_weatherapp_WeatherNative_getHourlyData(JNIEnv *env, jobject obj, jobject weatherDataObj, jint index) {
    // Hämta WeatherData-objektets klass och fältet "data"
    jclass weatherDataClass = (*env)->GetObjectClass(env, weatherDataObj);
    jfieldID dataField = (*env)->GetFieldID(env, weatherDataClass, "data", "Ljava/util/List;");
    jobject dataList = (*env)->GetObjectField(env, weatherDataObj, dataField);

    // Hämta HourlyWeatherData-objektet vid indexet från listan
    jclass listClass = (*env)->GetObjectClass(env, dataList);
    jmethodID getMethod = (*env)->GetMethodID(env, listClass, "get", "(I)Ljava/lang/Object;");
    jobject hourlyDataObj = (*env)->CallObjectMethod(env, dataList, getMethod, index);

    return hourlyDataObj;
}


JNIEXPORT void JNICALL Java_com_example_weatherapp_WeatherNative_addHourlyData(JNIEnv *env, jobject thisObj, jobject dataObj, jobject hourlyDataObj) {
    jclass dataClass = (*env)->GetObjectClass(env, dataObj);
    jfieldID dataField = (*env)->GetFieldID(env, dataClass, "data", "Ljava/util/List;");
    jobject dataListObj = (*env)->GetObjectField(env, dataObj, dataField);

    jclass listClass = (*env)->FindClass(env, "java/util/List");
    jmethodID addMethod = (*env)->GetMethodID(env, listClass, "add", "(Ljava/lang/Object;)Z");

    jclass hourlyDataClass = (*env)->FindClass(env, "com/example/weatherapp/WeatherNative$HourlyWeatherData");
    jmethodID getTimeMethod = (*env)->GetMethodID(env, hourlyDataClass, "getTime", "()Ljava/lang/String;");
    jmethodID getTemperatureMethod = (*env)->GetMethodID(env, hourlyDataClass, "getTemperature", "()Ljava/lang/String;");
    jmethodID getIconMethod = (*env)->GetMethodID(env, hourlyDataClass, "getIcon", "()Ljava/lang/String;");

    jstring timeJStr = (jstring)(*env)->CallObjectMethod(env, hourlyDataObj, getTimeMethod);
    jstring temperatureJStr = (jstring)(*env)->CallObjectMethod(env, hourlyDataObj, getTemperatureMethod);
    jstring iconJStr = (jstring)(*env)->CallObjectMethod(env, hourlyDataObj, getIconMethod);

    const char *time = (*env)->GetStringUTFChars(env, timeJStr, 0);
    const char *temperature = (*env)->GetStringUTFChars(env, temperatureJStr, 0);
    const char *icon = (*env)->GetStringUTFChars(env, iconJStr, 0);

    jobject newHourlyDataObj = (*env)->AllocObject(env, hourlyDataClass);
    jmethodID setTimeMethod = (*env)->GetMethodID(env, hourlyDataClass, "setTime", "(Ljava/lang/String;)V");
    jmethodID setTemperatureMethod = (*env)->GetMethodID(env, hourlyDataClass, "setTemperature", "(Ljava/lang/String;)V");
    jmethodID setIconMethod = (*env)->GetMethodID(env, hourlyDataClass, "setIcon", "(Ljava/lang/String;)V");

    jstring newTimeStr = (*env)->NewStringUTF(env, time);
    jstring newTemperatureStr = (*env)->NewStringUTF(env, temperature);
    jstring newIconStr = (*env)->NewStringUTF(env, icon);

    (*env)->CallVoidMethod(env, newHourlyDataObj, setTimeMethod, newTimeStr);
    (*env)->CallVoidMethod(env, newHourlyDataObj, setTemperatureMethod, newTemperatureStr);
    (*env)->CallVoidMethod(env, newHourlyDataObj, setIconMethod, newIconStr);

    (*env)->CallBooleanMethod(env, dataListObj, addMethod, newHourlyDataObj);

    (*env)->ReleaseStringUTFChars(env, timeJStr, time);
    (*env)->ReleaseStringUTFChars(env, temperatureJStr, temperature);
    (*env)->ReleaseStringUTFChars(env, iconJStr, icon);
}





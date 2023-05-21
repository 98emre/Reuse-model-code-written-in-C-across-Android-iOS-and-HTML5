
## Kom igång manual för att köra Android applikation som använder modellkod skriven i C.

**OBS!!** Först måste du ladda ner projektet från GitHub innan du börjar. Den här manualen är till för de som ska ladda ner och köra projektet på Android Studio första gången. 

1. När du öppnar projektet med Android Studio första gången så kommer man få ett felmeddelande. Klicka på OK. Android Studio klagar att den kan inte hitta SDK. Men vi låter Android Studio ändra till den SDK som finns tillgängligt på sin lokala dator. Bilden nedan visar hur felmeddelandet ser ut.

<img width="441" alt="bild" src="https://github.com/shch99/KTHExamensarbete2023/assets/131250228/c57e9bb1-c370-4c9f-b20e-c8a29122bb76">


2. Därefter provkör applikationen. Du bör få felmeddelande om build [CXX1409]. Det beror på att Android hittar inte självaste projektmappen och biblioteken på android gradle build filen. Man måste lägga till korrekt path så att Android kan hitta projektet på datorn. Samt du  måste ändra på `buildFiles`, `cleanCommandsComponents`, `buildTargetsCommandComponents`, `libraries` och `toolchains` för att applikationen ska kunna köra. Detta gäller för filerna på `android_gradle_build.json` specifikt `arm16-v8a` och `armeabi-v7a`. 

```json
{
  "buildFiles": [
    "/Users/AndroidStudioProjects/WeatherAppCAPI/app/src/main/cpp/CMakeLists.txt"
  ],
  "cleanCommandsComponents": [
    [
      "/Users/Library/Android/sdk/cmake/3.22.1/bin/ninja",
      "-C",
      "/Users/AndroidStudioProjects/WeatherAppCAPI/app/.cxx/Debug/6v5x5n2j/armeabi-v7a",
      "clean"
    ]
  ],
  "buildTargetsCommandComponents": [
    "/Users/Library/Android/sdk/cmake/3.22.1/bin/ninja",
    "-C",
    "/Users/AndroidStudioProjects/WeatherAppCAPI/app/.cxx/Debug/6v5x5n2j/armeabi-v7a",
    "{LIST_OF_TARGETS_TO_BUILD}"
  ],
  "libraries": {
    "JniBridge::@6890427a1f51a3e7e1df": {
      "toolchain": "toolchain",
      "abi": "armeabi-v7a",
      "artifactName": "JniBridge",
      "output": "/Users/AndroidStudioProjects/WeatherAppCAPI/app/build/intermediates/cxx/Debug/6v5x5n2j/obj/armeabi-v7a/libJniBridge.so",
      "runtimeFiles": [
        "/Users/AndroidStudioProjects/WeatherAppCAPI/app/build/intermediates/cxx/Debug/6v5x5n2j/obj/armeabi-v7a/libweather.so"
      ]
    },
    "weather::@6890427a1f51a3e7e1df": {
      "toolchain": "toolchain",
      "abi": "armeabi-v7a",
      "artifactName": "weather",
      "output": "/Users/



3.	Därefter är du redo att köra applikationen.

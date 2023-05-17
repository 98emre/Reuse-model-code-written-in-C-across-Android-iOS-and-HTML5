cmake_minimum_required(VERSION 3.22.1)


project("weather")

add_library(weather SHARED Model.c)
add_library(JniBridge SHARED JniBridge.c)

find_library(log-lib log )

target_link_libraries(weather ${log-lib} )
target_link_libraries(JniBridge PRIVATE weather)



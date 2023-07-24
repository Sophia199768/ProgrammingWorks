cmake_minimum_required(VERSION 3.24)
project(weather_lab)

set(CMAKE_CXX_STANDARD 17)
find_package( Curses REQUIRED )
find_package(CURL REQUIRED)
include_directories( ${CURSES_INCLUDE_DIRS} )
include_directories(${CURL_INCLUDE_DIRS} )

add_executable(weather_lab weather.cpp config.h pictures.h) # weather.cpp config.h
target_link_libraries(weather_lab ${CURSES_LIBRARIES} )
target_link_libraries(weather_lab ${CURL_LIBRARIES} )
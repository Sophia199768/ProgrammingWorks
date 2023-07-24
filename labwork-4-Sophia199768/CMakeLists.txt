cmake_minimum_required(VERSION 3.23)
project(laba_4)

add_subdirectory(lib)
set(CMAKE_CXX_STANDARD 14)

add_executable(laba_4 archiver.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE coding decoding)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

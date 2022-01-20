cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

project(QMidi LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 COMPONENTS Core Widgets)
if (NOT Qt6_FOUND)
    find_package(Qt5 5.15 COMPONENTS Core REQUIRED)
endif()

add_library(${PROJECT_NAME} STATIC "qmidiin.cpp" "qmidimapper.cpp" "qmidiout.cpp" "qmidipianoroll.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/libs/rtmidi)

target_link_libraries(${PROJECT_NAME} PUBLIC Qt::Core Qt::Widgets)
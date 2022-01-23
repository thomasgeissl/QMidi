cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

project(QMidi LANGUAGES CXX)

option(USE_JACK "Use JACK on Linux else ALSA." OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 COMPONENTS Core Widgets)
if (NOT Qt6_FOUND)
    find_package(Qt5 5.15 COMPONENTS Core REQUIRED)
endif()

add_library(${PROJECT_NAME} STATIC "qmidiin.cpp" "qmidimapper.cpp" "qmidiout.cpp" "qmidipianoroll.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/libs/rtmidi)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    set(MMLIB winmm)
    target_compile_definitions(${PROJECT_NAME} PUBLIC __WINDOWS_MM__)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    if(${USE_JACK})
        set(MMLIB jack)
        target_compile_definitions(${PROJECT_NAME} PUBLIC __LINUX_JACK__)
    else()
        set(MMLIB asound)
        target_compile_definitions(${PROJECT_NAME} PUBLIC __LINUX_ALSA__)
    endif()
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    set(MMLIB CoreMidi CoreAudio CoreFoundation)
    target_compile_definitions(${PROJECT_NAME} PUBLIC __MACOSX_CORE__)
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC ${MMLIB} Qt::Core Qt::Widgets)

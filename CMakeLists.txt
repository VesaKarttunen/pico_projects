cmake_minimum_required(VERSION 3.31)

set(CMAKE_C_STANDARD   23)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

set(PICO_BOARD    pico2_w)
set(PICO_PLATFORM rp2350-arm-s)

include(pico-sdk/pico_sdk_init.cmake)

project(PicoProjects
    LANGUAGES C CXX ASM
    DESCRIPTION "Pico 2W based hobby projects")

pico_sdk_init()

set(FREERTOS_KERNEL_PATH ${CMAKE_CURRENT_LIST_DIR}/FreeRTOS-Kernel)
include(cmake/FreeRTOS_Kernel_import.cmake)

include(cmake/compiler_warning_options.cmake)

if(NOT (WIFI_SSID AND WIFI_PASSWORD))
    message("Wi-Fi SSID and/or password are missing from command line arguments")
    message("Give -D WIFI_SSID=<ssid> -D WIFI_PASSWORD=<password> in cmake configuration step to allow connecting into Wi-Fi")

    set(WIFI_SSID     dummy_ssid)
    set(WIFI_PASSWORD dummy_password)
endif()

add_subdirectory(plain_pico)
add_subdirectory(sensor_kit)

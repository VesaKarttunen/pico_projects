cmake_minimum_required(VERSION 3.31)

set(CMAKE_C_STANDARD   23)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_SCAN_FOR_MODULES    OFF)

set(PICO_BOARD    pico2_w)
set(PICO_PLATFORM rp2350-arm-s)

include(third_party/pico-sdk/pico_sdk_init.cmake)

project(PicoProjects
    LANGUAGES C CXX ASM
    DESCRIPTION "Pico 2W based hobby projects")

pico_sdk_init()

if(NOT (WIFI_SSID AND WIFI_PASSWORD AND HTTP_SERVER_URL))
    message("Wi-Fi SSID, password, or HTTP server URL are missing from command line arguments")
    message("Give -D WIFI_SSID=<ssid> -D WIFI_PASSWORD=<password> -D HTTP_SERVER_URL=<url> in cmake configuration step to allow connecting into Wi-Fi")

    set(WIFI_SSID       dummy_ssid)
    set(WIFI_PASSWORD   dummy_password)
    set(HTTP_SERVER_URL http://0.0.0.0:80)
endif()

add_subdirectory(projects)
add_subdirectory(third_party)

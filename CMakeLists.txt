cmake_minimum_required(VERSION 4.0)

set(CMAKE_C_STANDARD   23)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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

add_subdirectory(basic_demo)

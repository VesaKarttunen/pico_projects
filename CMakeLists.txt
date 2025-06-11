cmake_minimum_required(VERSION 4.0)
 
set(CMAKE_C_STANDARD   23)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
 
set(PICO_BOARD pico2_w)
set(PICO_PLATFORM rp2350-arm-s)
 
include(pico-sdk/pico_sdk_init.cmake)
 
project(basic_demo
    C CXX ASM)
 
pico_sdk_init()
 
add_executable(basic_demo
    basic_demo/main.c)
 
target_link_libraries(basic_demo
    PRIVATE
        pico_stdlib
        pico_cyw43_arch_none
        hardware_adc)

pico_enable_stdio_usb(basic_demo ON)
pico_enable_stdio_uart(basic_demo ON)
 
pico_add_extra_outputs(basic_demo)
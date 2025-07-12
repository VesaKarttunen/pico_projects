project(PlainPico
    DESCRIPTION "Demo project using only Pico2W's own features and no extra HW")

set(SourceFiles
    app_command/app_command.cpp
    app_command/command_conf.cpp
    app_feedback/app_feedback.cpp
    led/led.cpp
    temperature/temperature.cpp
    wifi_comm/wifi_comm.cpp
    main.cpp)

set_source_files_properties(${SourceFiles}
    PROPERTIES COMPILE_OPTIONS
        "${CompilerWarningsAll}")

add_executable(plain_pico
    ${SourceFiles})

target_include_directories(plain_pico
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(plain_pico
    PRIVATE
        pico_stdlib
        pico_cyw43_arch_lwip_sys_freertos
        hardware_adc
        FreeRTOS-Kernel-Heap4)

if(NOT (WIFI_SSID AND WIFI_PASSWORD))
    message("Wi-Fi SSID and password missing from command line arguments\n")
    message("Give -D WIFI_SSID=<ssid> -D WIFI_PASSWORD=<password> in cmake configuration step\n")
endif()

target_compile_definitions(plain_pico
    PRIVATE
        SECRET_WIFI_SSID="${WIFI_SSID}"
        SECRET_WIFI_PASSWORD="${WIFI_PASSWORD}")

pico_enable_stdio_usb(plain_pico  ON)
pico_enable_stdio_uart(plain_pico OFF)

pico_add_extra_outputs(plain_pico)

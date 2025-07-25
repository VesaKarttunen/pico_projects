project(SensorKit
    DESCRIPTION "Demo project using Waveshare Electronics Sensor Kit B for Pico")

set(SourceFiles
    app_command/app_command.cpp
    app_command/command_conf.cpp
    app_feedback/app_feedback.cpp
    button/button.cpp
    led/led.cpp
    main.cpp
    rtos_task/rtos_task-setup.cpp
    temperature/temperature.cpp
    web_server/web_server.cpp
    wifi_comm/wifi_comm.cpp)

set_source_files_properties(${SourceFiles}
    PROPERTIES COMPILE_OPTIONS
        "${CompilerWarningsAll}")

add_executable(sensor_kit
    ${SourceFiles})

target_include_directories(sensor_kit
    PRIVATE
        ./
        ${CMAKE_SOURCE_DIR}/third_party/config)

target_link_libraries(sensor_kit
    PRIVATE
        mongoose
        pico_stdlib
        pico_cyw43_arch_lwip_sys_freertos
        hardware_adc
        FreeRTOS-Kernel-Heap4)

target_compile_definitions(sensor_kit
    PRIVATE
        WIFI_SSID="${WIFI_SSID}"
        WIFI_PASSWORD="${WIFI_PASSWORD}"
        HTTP_SERVER_URL="${HTTP_SERVER_URL}")

pico_enable_stdio_usb(sensor_kit  ON)
pico_enable_stdio_uart(sensor_kit OFF)

pico_add_extra_outputs(sensor_kit)

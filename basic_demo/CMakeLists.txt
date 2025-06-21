add_executable(basic_demo
    main.c)

target_include_directories(basic_demo
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(basic_demo
    PRIVATE
        pico_stdlib
        pico_cyw43_arch_none
        hardware_adc
        FreeRTOS-Kernel-Heap4)

pico_enable_stdio_usb(basic_demo ON)
pico_enable_stdio_uart(basic_demo ON)

pico_add_extra_outputs(basic_demo)
add_library(mongoose
    STATIC
        mongoose.c)

target_include_directories(mongoose
    SYSTEM PUBLIC
        ../
    PRIVATE
        ../config)

target_link_libraries(mongoose
    PRIVATE
        pico_stdlib_headers
        pico_cyw43_arch_lwip_sys_freertos_headers)
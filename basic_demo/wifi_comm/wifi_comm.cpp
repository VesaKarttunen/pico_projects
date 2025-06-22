// Own
#include "wifi_comm.hpp"

// Pico-SDK
#include "pico/cyw43_arch.h"

// STD
#include <cstdio>

// This init needs to be executed in a RTOS task because of it will also initialize
// lwIP stack which requires it or the init will fail.
void WifiComm::Init()
{
    cyw43_arch_init();
    cyw43_arch_enable_sta_mode();

    printf("Connecting to Wi-Fi...\n");

    // Wi-Fi SSID and password are given as command line arguments in cmake configuration step:
    // $ cmake -G "Ninja" -S <source-dir> -D WIFI_SSID=<ssid> -D WIFI_PASSWORD=<password>
    // Never write the password into source code directly!
    int error_code = cyw43_arch_wifi_connect_timeout_ms(SECRET_WIFI_SSID,
                                                        SECRET_WIFI_PASSWORD,
                                                        CYW43_AUTH_WPA2_AES_PSK,
                                                        30'000u);

    bool is_connection_successful = error_code == 0;

    if (is_connection_successful)
    {
        printf("Wi-Fi connected successfully\n");
    }
    else
    {
        printf("Wi-Fi connection failed\n");
    }
}

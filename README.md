# pico_projects
Repository for learning with Raspberry Pi Pico

## Build instructions
    mkdir <build-dir>
    cd <build-dir>
    cmake -G "Ninja" -S <source-dir> -D WIFI_SSID=<ssid> -D WIFI_PASSWORD=<password>
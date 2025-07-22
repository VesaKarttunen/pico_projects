# pico_projects
Raspberry Pico 2W based hobby projects.

## Repository structure
Top-level folders are structured as sub-projects with the following meaning:

- **plain_pico**: Demo project using only Pico 2W's own features without any extra HW. Thus, the only thing required to use the firmware produced by this project is the Pico 2W itself.
- **sensor_kit**: Demo project using Pico 2W with Waveshare Electronics Sensor Kit B.

## Build tools
To build and use the projects in this repository, the following SW tools are required:

- CMake
    - https://github.com/kitware/cmake/releases
    - $ winget install --id=Kitware.CMake --exact
    - $ sudo apt-get install -y cmake
    - Tested version: 4.0.3
- Ninja
    - https://github.com/ninja-build/ninja/releases
    - $ winget install --id=Ninja-build.Ninja --exact
    - $ sudo apt-get install -y ninja-build
    - Tested version: 1.13.1
- Python
    - https://www.python.org/downloads/
    - $ winget install --id=Python.Python.3.13 --exact
    - $ sudo apt-get install -y python3
    - Tested version: 3.13.5
- ARM-GNU Toolchain
    - https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads
    - $ winget install --id=Arm.GnuArmEmbeddedToolchain --exact
    - $ sudo apt-get install -y gcc-arm-none-eabi
    - Select: _"AArch32 bare-metal target"_ (arm-none-eabi)
    - Tested version: 14.3.rel1
- ARM-Clang Toolchain (alternative for ARM-GNU Toolchain)
    - https://github.com/arm/arm-toolchain/releases
    - Select: _"Arm Toolchain for Embedded"_ (ATfE)
    - Tested version: 20.1.0

The projects in this repository uses C++23 and aims for "Live at Head" approach with tools and dependencies. Thus, the latest stable version of all the dependencies and tools is aimed to be used in this repository.

## Build instructions
Build using ARM-GNU Toolchain (assumed to be in the PATH):

    $ mkdir <build-dir>
    $ cd    <build-dir>
    $ cmake -G Ninja -S <source-repo-dir> -D WIFI_SSID=<ssid> -D WIFI_PASSWORD=<password>

Build using ARM-Clang Toolchain:

    $ mkdir <build-dir>
    $ cd    <build-dir>
    $ cmake -G Ninja -S <source-repo-dir> -D PICO_COMPILER=pico_arm_clang -D PICO_TOOLCHAIN_PATH=<arm-clang-toolchain-dir> -D WIFI_SSID=<ssid> -D WIFI_PASSWORD=<password>

## Flashing instructions
Getting the Pico into BOOTSEL mode using the BOOTSEL button during board power-up is simple but it is somewhat inconvenient since Pico does not have reset button thus requiring manually disconnecting and then connecting the USB cable (or otherwise turning OFF and ON the power from Pico).

Instead, the recommended method is to use Picotool which allows programming and rebooting Pico without touching it at all.

Program and reboot Pico:

    $ picotool load -f -x <path-to-uf2-file>

Reboot Pico into BOOTSEL mode:

    $ picotool reboot -f -u

Reboot Pico into application mode:

    $ picotool reboot -f

Note that the above assumes the Picotool is in the PATH.

To build the latest version of Picotool from source (for Windows host), you can use the helper Powershell script in this repo as follows:

    $ mkdir <build-dir>
    $ cd    <build-dir>
    $ <source-repo-dir>/dev_tool/build_picotool.ps1

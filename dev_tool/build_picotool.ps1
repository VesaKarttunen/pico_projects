# This script assumes that the intended build directory for the picotool is the present Powershell's working directory
# Thus call this script as follows:
# $ mkdir <picotool-build-dir>
# $ cd    <picotool-build-dir>
# $ <path-to-this-script>/build_picotool.ps1

$build_dir = Get-Location

# Clone all the repositories require to build Picotool
git clone https://github.com/raspberrypi/picotool.git --branch develop --depth 1
git clone https://github.com/libusb/libusb-cmake.git  --branch main    --depth 1
git clone https://github.com/raspberrypi/pico-sdk.git --branch develop --depth 1 --shallow-submodules --recurse-submodules=lib/mbedtls

# Build libusb
cmake -G Ninja -S ./libusb-cmake -B ./libusb-cmake/build
cmake --build ./libusb-cmake/build

# Build and install Picotool
cmake -G Ninja -S ./picotool -B ./picotool/build -D PICO_SDK_PATH=$build_dir/pico-sdk -D LIBUSB_LIBRARIES=$build_dir/libusb-cmake/build/libusb-1.0.a -D LIBUSB_INCLUDE_DIR=$build_dir/libusb-cmake/libusb/libusb
cmake --build   ./picotool/build
cmake --install ./picotool/build --prefix ./picotool-install

# Remove sources and intermediate artifacts
Remove-Item ./picotool     -Force -Recurse
Remove-Item ./libusb-cmake -Force -Recurse
Remove-Item ./pico-sdk     -Force -Recurse

# After the build is complete, add <build-dir>/picotool-install/bin to PATH.
# Note that you can relocate and rename the directory <build-dir>/picotool-install as you wish.
# Simply copy/cut the whole directory and place it in your desired location with any name you like.

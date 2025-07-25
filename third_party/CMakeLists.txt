set(FREERTOS_KERNEL_PATH ${CMAKE_CURRENT_LIST_DIR}/FreeRTOS-Kernel)
# Directory of the Pico2 (RP2350) port of the FreeRTOS
add_subdirectory(FreeRTOS-Kernel/portable/ThirdParty/Community-Supported-Ports/GCC/RP2350_ARM_NTZ)

add_subdirectory(mongoose)

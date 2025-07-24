//---------------------------------------------------------------------------------------------------------------------
// Main
//---------------------------------------------------------------------------------------------------------------------

// Local project
#include "rtos_task/rtos_task-setup.hpp"

// Pico SDK
#include "pico/stdlib.h"

// FreeRTOS
#include "FreeRTOS.h"
#include "task.h"

//---------------------------------------------------------------------------------------------------------------------
// MAIN FUNCTION DEFINITION
//---------------------------------------------------------------------------------------------------------------------

int main()
{
    InitNonBlockingModules();

    // Short delay to give time to connect UART after reboot
    sleep_ms(5000u);

    CreateRtosTasks();

    vTaskStartScheduler();
}

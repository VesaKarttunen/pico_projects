//---------------------------------------------------------------------------------------------------------------------
// Main
//---------------------------------------------------------------------------------------------------------------------

// Local project
#include "button/button.hpp"
#include "led/led.hpp"
#include "temperature/temperature.hpp"
#include "utility/rtos_priority_levels.hpp"
#include "wifi_comm/wifi_comm.hpp"

// Pico SDK
#include "pico/stdlib.h"

// FreeRTOS
#include "FreeRTOS.h"
#include "task.h"

// STD
#include <cstdio>

//---------------------------------------------------------------------------------------------------------------------
// PRIVATE FUNCTION DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

static void TaskPeriodic_60s(void* p)
{
    (void)p;

    TickType_t ticks_previous_wake = xTaskGetTickCount();

    while (true)
    {
        xTaskDelayUntil(&ticks_previous_wake, pdMS_TO_TICKS(60'000));

        double pcb_temperature_C = static_cast<double>(Temperature::GetPcbTemperature_C());
        std::printf("PCB temperature = %.2f C\n", pcb_temperature_C);
    }
}

static void TaskPeriodic_100ms(void* p)
{
    (void)p;

    TickType_t ticks_previous_wake = xTaskGetTickCount();

    while (true)
    {
        xTaskDelayUntil(&ticks_previous_wake, pdMS_TO_TICKS(100));

        g_led.TaskPeriodic_100ms();
    }
}

static void TaskPeriodic_1s(void* p)
{
    (void)p;

    TickType_t ticks_previous_wake = xTaskGetTickCount();

    while (true)
    {
        xTaskDelayUntil(&ticks_previous_wake, pdMS_TO_TICKS(1000));

        // No work at the moment
    }
}

// Initialization actions that need to be executed inside a RTOS task
static void TaskInit(void* p)
{
    (void)p;

    WifiComm::Init();

    // Once completed, this initialization task will delete itself
    vTaskDelete(nullptr);
}

//---------------------------------------------------------------------------------------------------------------------
// MAIN FUNCTION DEFINITION
//---------------------------------------------------------------------------------------------------------------------

int main()
{
    stdio_init_all();
    Temperature::Init();
    Led::Init();
    Button::Init();

    // Short delay to give time to connect UART after reboot
    sleep_ms(5000u);

    xTaskCreate(TaskInit,
                "TaskInit",
                configMINIMAL_STACK_SIZE,
                nullptr,
                TaskPriority::VERY_HIGH_5,
                nullptr);

    xTaskCreate(TaskPeriodic_100ms,
                "TaskPeriodic_100ms",
                configMINIMAL_STACK_SIZE,
                nullptr,
                TaskPriority::HIGH_4,
                nullptr);

    xTaskCreate(TaskPeriodic_1s,
                "TaskPeriodic_1s",
                configMINIMAL_STACK_SIZE,
                nullptr,
                TaskPriority::MID_3,
                nullptr);

    xTaskCreate(TaskPeriodic_60s,
                "TaskPeriodic_60s",
                configMINIMAL_STACK_SIZE,
                nullptr,
                TaskPriority::LOW_2,
                nullptr);

    vTaskStartScheduler();
}

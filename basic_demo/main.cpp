// Local project
#include "led/led.hpp"
#include "temperature/temperature.hpp"
#include "wifi_comm/wifi_comm.hpp"

// Pico-SDK
#include "pico/stdlib.h"

// FreeRTOS
#include "FreeRTOS.h"
#include "task.h"

// STD
#include <cstdio>

static void TaskPeriodic_5s(void* p)
{
    (void)p;

    TickType_t ticks_previous_wake = xTaskGetTickCount();

    while (true)
    {
        xTaskDelayUntil(&ticks_previous_wake, pdMS_TO_TICKS(5000));

        const float pcb_temperature_C = Temperature::GetPcbTemperature_C();
        printf("PCB temperature = %.02f C\n", pcb_temperature_C);
    }
}

static void TaskPeriodic_1s(void* p)
{
    (void)p;

    TickType_t ticks_previous_wake = xTaskGetTickCount();

    while (true)
    {
        xTaskDelayUntil(&ticks_previous_wake, pdMS_TO_TICKS(1000));

        static bool toggle;
        toggle = !toggle;
        Led::SetState(toggle);
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

int main()
{
    stdio_init_all();
    Temperature::Init();

    xTaskCreate(TaskInit,
                "TaskInit",
                configMINIMAL_STACK_SIZE,
                nullptr,
                5,
                nullptr);

    xTaskCreate(TaskPeriodic_1s,
                "TaskPeriodic_1s",
                configMINIMAL_STACK_SIZE,
                nullptr,
                4,
                nullptr);

    xTaskCreate(TaskPeriodic_5s,
                "TaskPeriodic_5s",
                configMINIMAL_STACK_SIZE,
                nullptr,
                3,
                nullptr);

    vTaskStartScheduler();
}

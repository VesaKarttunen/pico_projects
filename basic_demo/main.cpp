// Local project
#include "led/led.hpp"
#include "temperature/temperature.hpp"

// Pico-SDK
#include "pico/stdlib.h"

// FreeRTOS
#include "FreeRTOS.h"
#include "task.h"

//STD
#include <cstdio>

void TaskPeriodic_5s(void* p)
{
    (void)p;

    TickType_t ticks_previous_wake = xTaskGetTickCount();

    while (true)
    {
        const bool ok = xTaskDelayUntil(&ticks_previous_wake, pdMS_TO_TICKS(5000)) == pdTRUE;

        if (!ok)
        {
            printf("Missed scheduler deadline");
        }

        const float pcb_temperature_C = Temperature::GetPcbTemperature_C();
        printf("PCB temperature = %.02f C\n", pcb_temperature_C);
    }
}

void TaskPeriodic_1s(void* p)
{
    (void)p;

    TickType_t ticks_previous_wake = xTaskGetTickCount();

    while (true)
    {
        const bool ok = xTaskDelayUntil(&ticks_previous_wake, pdMS_TO_TICKS(1000)) == pdTRUE;

        if (!ok)
        {
            printf("Missed scheduler deadline");
        }

        static bool toggle;
        toggle = !toggle;

        Led::SetState(toggle);
    }
}

int main()
{
    stdio_init_all();
    Led::Init();
    Temperature::Init();

    xTaskCreate(TaskPeriodic_5s,
                "Task1",
                configMINIMAL_STACK_SIZE,
                nullptr,
                3,
                nullptr);

    xTaskCreate(TaskPeriodic_1s,
                "Task2",
                configMINIMAL_STACK_SIZE,
                nullptr,
                4,
                nullptr);

    // Start the RTOS scheduler (infinite loop)
    vTaskStartScheduler();
}

#include "hardware/adc.h"
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
 
#include "FreeRTOS.h"
#include "task.h"
 
#include <stdio.h>
 
float ReadOnboardTemperature() {
 
  /* 12-bit conversion, assume max value == ADC_VREF == 3.3 V */
  const float conversionFactor = 3.3f / (1 << 12);
 
  float adc = (float)adc_read() * conversionFactor;
  float tempC = 27.0f - (adc - 0.706f) / 0.001721f;
 
  return tempC;
}
 
void EnableLed(bool is_enabled) {
  cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, is_enabled);
}
 
 
void TaskPeriodic_5s(void* p) {
  (void)p;
 
    TickType_t ticks_previous_wake = xTaskGetTickCount();
 
    while (true)
    {
        const bool ok = xTaskDelayUntil(&ticks_previous_wake, pdMS_TO_TICKS(5000)) == pdTRUE;
 
        if (!ok)
        {
            printf("Missed scheduler deadline");
        }
 
        printf("Onboard temperature = %.02f C\n", ReadOnboardTemperature());
    }
}
 
void TaskPeriodic_1s(void* p) {
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
 
        EnableLed(toggle);
    }
}
 
int main()
{
  cyw43_arch_init();
  stdio_init_all();
  adc_init();
  adc_set_temp_sensor_enabled(true);
  adc_select_input(4);
 
  while (true)
  {
    xTaskCreate(TaskPeriodic_5s,
                "Task1",
                configMINIMAL_STACK_SIZE,
                NULL,
                3,
                NULL);
 
    xTaskCreate(TaskPeriodic_1s,
                "Task2",
                configMINIMAL_STACK_SIZE,
                NULL,
                4,
                NULL);
 
    // Start the RTOS scheduler (infinite loop)
    vTaskStartScheduler();
  }
}
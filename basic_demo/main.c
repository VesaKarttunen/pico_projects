#include "hardware/adc.h"
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"

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

int main() {
  cyw43_arch_init();
  stdio_init_all();
  adc_init();
  adc_set_temp_sensor_enabled(true);
  adc_select_input(4);

  while (true) {

    printf("Onboard temperature = %.02f C\n", ReadOnboardTemperature());
    EnableLed(true);
    sleep_ms(2000u);
    EnableLed(false);
    sleep_ms(2000u);
  }
}
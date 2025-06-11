#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"

#include <stdio.h>

void EnableLed(bool is_enabled) {
  cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, is_enabled);
}

int main() {
  cyw43_arch_init();
  stdio_init_all();

  while (true) {
    printf("Hello, world!\n");
    EnableLed(true);
    sleep_ms(500u);
    EnableLed(false);
    sleep_ms(500u);
  }
}
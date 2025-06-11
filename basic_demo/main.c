#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"

void EnableLed(bool is_enabled) {
  cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, is_enabled);
}

int main() {
  int status = cyw43_arch_init();
  hard_assert(status == PICO_OK);

  while (true) {
    EnableLed(true);
    sleep_ms(500u);
    EnableLed(false);
    sleep_ms(500u);
  }
}
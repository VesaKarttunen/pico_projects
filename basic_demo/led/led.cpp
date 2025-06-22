//Own
#include "led.hpp"

// Pico-SDK
#include "pico/cyw43_arch.h"

void Led::SetState(bool is_enabled)
{
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, is_enabled);
}

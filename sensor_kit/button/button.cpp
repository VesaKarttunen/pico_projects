// Own
#include "button.hpp"

// Pico-SDK
#include "pico/stdlib.h"

void Button::ButtonInit()
{
    uint button_pin = 3u;
    gpio_init(button_pin);
    gpio_set_dir(button_pin, GPIO_IN);
    gpio_pull_up(button_pin);
}

bool Button::GetButtonState()
{
    uint button_pin = 3u;
    return gpio_get(button_pin);
}

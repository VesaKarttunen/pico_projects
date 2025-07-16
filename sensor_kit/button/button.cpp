// Own
#include "button.hpp"

// Pico-SDK
#include "pico/stdlib.h"

//---------------------------------------------------------------------------------------------------------------------
// PRIVATE (STATIC) CONSTANT DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

// Waveshare sensor board has button connected to GPIO pin 3
static constexpr unsigned button_pin = 3u;

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC MEMBER FUNCTION DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

void Button::Init()
{
    gpio_init(button_pin);
    gpio_set_dir(button_pin, static_cast<bool>(GPIO_IN));
    gpio_pull_up(button_pin);
}

bool Button::IsPressed()
{
    return !gpio_get(button_pin);
}

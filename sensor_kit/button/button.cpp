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

bool Button::Toggle()
{
    bool current_state = IsPressed();

    if (current_state && !m_previous_state)
    {
        m_toggled_state = !m_toggled_state;
    }

    m_previous_state = current_state;
    return m_toggled_state;
}

Button g_button;

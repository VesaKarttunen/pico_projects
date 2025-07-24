//---------------------------------------------------------------------------------------------------------------------
// Button
//---------------------------------------------------------------------------------------------------------------------

// Own
#include "button.hpp"

// Pico SDK
#include "pico/stdlib.h"

//---------------------------------------------------------------------------------------------------------------------
// PRIVATE CONSTANT DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

// Waveshare sensor board has button connected to GPIO pin 3
static constexpr unsigned f_button_pin = 3u;

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC MEMBER FUNCTION DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

void Button::Init()
{
    gpio_init(f_button_pin);
    gpio_set_dir(f_button_pin, static_cast<bool>(GPIO_IN));
    gpio_pull_up(f_button_pin);
}

bool Button::IsPressed()
{
    return !gpio_get(f_button_pin);
}

// Returns rising edge detection status for a button press.
// Identifies when a button's state changes from OFF (not pressed) to ON (is pressed).
bool Button::IsPressRisingEdge()
{
    bool is_pressed_now = IsPressed();

    // Button press rising edge happens when button is now pressed and it was previously not pressed
    bool is_press_rising_edge = is_pressed_now && !m_was_pressed_previously;
    m_was_pressed_previously  = is_pressed_now;

    return is_press_rising_edge;
}

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC VARIABLE DEFINITIONS/INSTANTIATIONS
//---------------------------------------------------------------------------------------------------------------------

Button g_button;

// Own
#include "led.hpp"

// Local-project
#include "button/button.hpp"

// Pico-SDK
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"

//---------------------------------------------------------------------------------------------------------------------
// PRIVATE (STATIC) CONSTANT DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

// Waveshare sensor board has LED connected to GPIO pin 10
static constexpr unsigned led_pin = 10u;

void Led::Init()
{
    gpio_init(led_pin);
    gpio_set_dir(led_pin, static_cast<bool>(GPIO_OUT));
    gpio_put(led_pin, true);
}

void Led::SetMode(LedMode mode)
{
    m_mode = mode;
}

void Led::TaskPeriodic_100ms()
{
    bool previous_led_state = m_led_state;

    switch (m_mode)
    {
        case LedMode::OFF:
        default:
        {
            m_led_state = false;
            break;
        }
        case LedMode::ON:
        {
            m_led_state = true;
            break;
        }
        case LedMode::BLINKING:
        {
            float task_period_s = 0.1f;
            m_timer_s          += task_period_s;

            if (m_timer_s >= (0.5f * m_blinking_period_s))
            {
                m_timer_s   = 0.0f;
                m_led_state = !m_led_state;
            }

            break;
        }
        case LedMode::BUTTON_PRESS:
        {
            m_led_state = Button::IsPressed();
            break;
        }
        case LedMode::BUTTON_TOGGLE:
        {
            if (g_button.IsPressRisingEdge())
            {
                m_led_state = !m_led_state;
            }

            break;
        }
    }

    // Call LED IO pin setting function only if LED state changes
    if (m_led_state != previous_led_state)
    {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, m_led_state);
        gpio_put(led_pin, !m_led_state);
    }
}

void Led::SetBlinkingPeriod_s(float period_s)
{
    m_blinking_period_s = period_s;
}

Led g_led;

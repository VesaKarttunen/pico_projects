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

// Waveshare sensor board has led connected to GPIO pin 10
static constexpr unsigned led_pin = 10u;

void Led::Init()
{
    gpio_init(led_pin);
    gpio_set_dir(led_pin, static_cast<bool>(GPIO_OUT));
}

void Led::SetMode(LedMode mode)
{
    m_mode = mode;
}

void Led::TaskPeriodic_100ms()
{
    bool previous_led_state = m_led_state;

    if (m_mode == LedMode::OFF)
    {
        m_led_state = false;
    }
    else if (m_mode == LedMode::ON)
    {
        m_led_state = true;
    }
    else if (m_mode == LedMode::BLINKING)
    {
        float task_period_s = 0.1f;
        m_timer_s          += task_period_s;

        if (m_timer_s >= (0.5f * m_blinking_period_s))
        {
            m_timer_s   = 0.0f;
            m_led_state = !m_led_state;
        }
    }
    else if (m_mode == LedMode::BUTTON)
    {
        m_led_state = Button::IsPressed();
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

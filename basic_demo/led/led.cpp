// Own
#include "led.hpp"

// Pico-SDK
#include "pico/cyw43_arch.h"

void Led::SetLedMode(LedMode mode)
{
    m_mode = mode;
}

void Led::TaskPeriodic_100ms()
{
    if (m_mode == LedMode::OFF)
    {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, false);
    }
    else if (m_mode == LedMode::ON)
    {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, true);
    }
    else if (m_mode == LedMode::BLINKING)
    {
        m_counter++;
        if (m_counter > m_counter_limit)
        {
            m_toggle  = !m_toggle;
            m_counter = 0;
        }
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, m_toggle);
    }
}

void Led::SetBlinkingPeriod_s(float period_s)
{
    m_counter_limit = static_cast<int>((period_s / 2.0f) / 0.1f);
}

Led g_led;

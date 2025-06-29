// Own
#include "app_command.hpp"

// Local-project
#include "led/led.hpp"

// STD
#include <cstdio>

void AppCommand::ProcessCommand(std::string_view command)
{
    if (command == "led_on")
    {
        g_led.SetLedMode(LedMode::ON);
    }
    else if (command == "led_off")
    {
        g_led.SetLedMode(LedMode::OFF);
    }
    else if (command == "led_blink")
    {
        g_led.SetLedMode(LedMode::BLINKING);
    }
    else if (command == "led_period_5s")
    {
        g_led.SetBlinkingPeriod_s(5.0);
    }
    else
    {
        std::printf("Unknown command: %s\n", command.data());
        std::printf("Use 'led_on' or 'led_off' to control the LED\n");
    }
}

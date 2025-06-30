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
    else if (command == "led_blinking_period_5s")
    {
        g_led.SetBlinkingPeriod_s(5.0);
    }
    else
    {
        std::printf("Unknown command: %s\n", command.data());
        std::printf("Available commands are:\n");
        std::printf("led_off\n");
        std::printf("led_on\n");
        std::printf("led_blink\n");
        std::printf("led_blinking_period_5s\n");
    }
}

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
        Led::SetState(true);
    }
    else if (command == "led_off")
    {
        Led::SetState(false);
    }
    else
    {
        printf("Unknown command: %s\n", command);
        printf("Use 'led_on' and 'led_off' to control the LED\n", command);
    }
}

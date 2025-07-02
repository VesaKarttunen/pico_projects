// Own
#include "app_command.hpp"

// Local-project
#include "led/led.hpp"

// STD
#include <cstdio>

using CommandHookFunc = void (*)(float);

struct CommandHookMap
{
    std::string_view name;
    CommandHookFunc hook_function;
};

// clang-format off
static std::array<CommandHookMap, 2> command_conf{
    CommandHookMap{"SetLedMode",        [](float mode)    { g_led.SetLedMode(static_cast<LedMode>(mode)); }},
    CommandHookMap{"SetBlinkingPeriod", [](float period_s){ g_led.SetBlinkingPeriod_s(period_s); }}
};
// clang-format on

void AppCommand::ProcessCommand(const CommandFrame& requested_command)
{
    bool found_command = false;

    for (auto available_command : command_conf)
    {
        std::string_view requested_command_name = requested_command.name.data();

        if (available_command.name == requested_command_name)
        {
            available_command.hook_function(requested_command.arqument);
            found_command = true;
        }
    }
    if (!found_command)
    {
        // NOLINTNEXTLINE(*stringview-data-usage)
        std::printf("Unknown command: %s\n", requested_command.name.data());
    }
}

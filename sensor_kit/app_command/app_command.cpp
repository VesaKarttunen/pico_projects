// Own
#include "app_command.hpp"
#include "command_conf.hpp"

// STD
#include <cstdio>
#include <string_view>

void AppCommand::ProcessCommand(const CommandFrame& requested_command)
{
    bool found_valid_command = false;

    for (auto available_command : CommandConf::GetSupportedCommands())
    {
        std::string_view requested_command_name = requested_command.name.data();

        if (available_command.name == requested_command_name)
        {
            available_command.hook_func(requested_command.argument);
            found_valid_command = true;
        }
    }

    if (!found_valid_command)
    {
        // NOLINTNEXTLINE(*stringview-data-usage)
        std::printf("Unknown command: %s\n", requested_command.name.data());
    }
}

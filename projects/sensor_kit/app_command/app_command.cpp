//---------------------------------------------------------------------------------------------------------------------
// Application Commands
//---------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------
// PRIVATE INCLUDE DIRECTIVES
//---------------------------------------------------------------------------------------------------------------------

// Own
#include "app_command.hpp"
#include "command_conf.hpp"

// STD
#include <cstdio>
#include <string_view>

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC MEMBER FUNCTION DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

bool AppCommand::ProcessCommand(const AppCommandInput& requested_command)
{
    bool is_success = false;

    for (auto available_command : CommandConf::GetSupportedCommands())
    {
        if (available_command.name == requested_command.name)
        {
            is_success = available_command.hook_func(requested_command.arg);
            break;
        }
    }

    if (!is_success)
    {
        std::printf("Command API call failed\n");
    }

    return is_success;
}

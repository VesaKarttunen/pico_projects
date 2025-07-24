//---------------------------------------------------------------------------------------------------------------------
// Supported Commands Conf
//---------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------
// PRIVATE INCLUDE DIRECTIVES
//---------------------------------------------------------------------------------------------------------------------

// Own
#include "command_conf.hpp"

// Local project
#include "led/led.hpp"

// STD
#include <array>
#include <span>

//---------------------------------------------------------------------------------------------------------------------
// PRIVATE FUNCTION DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

static void SetLedMode(float mode)
{
    g_led.SetMode(static_cast<LedMode>(mode));
}

static void SetLedBlinkingPeriod_s(float period_s)
{
    g_led.SetBlinkingPeriod_s(period_s);
}

//---------------------------------------------------------------------------------------------------------------------
// PRIVATE VARIABLE DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

// clang-format off
// NOLINTNEXTLINE(*interfaces-global-init)
static std::array<CommandHookMap, 2> supported_commands{{
    {.name      = "SetLedMode",
     .hook_func = SetLedMode},
    {.name      = "SetLedBlinkingPeriod_s",
     .hook_func = SetLedBlinkingPeriod_s}
}};
// clang-format on

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC MEMBER FUNCTION DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

std::span<CommandHookMap> CommandConf::GetSupportedCommands()
{
    return supported_commands;
}

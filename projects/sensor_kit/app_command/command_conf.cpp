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
#include "utility/string_conversion.hpp"

// STD
#include <array>
#include <span>

//---------------------------------------------------------------------------------------------------------------------
// PRIVATE FUNCTION DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

static bool SetLedMode(std::string_view arg)
{
    bool is_arg_valid = true;
    LedMode mode      = LedMode::OFF;

    if (arg == "ON")
    {
        mode = LedMode::ON;
    }
    else if (arg == "OFF")
    {
        mode = LedMode::OFF;
    }
    else if (arg == "BLINKING")
    {
        mode = LedMode::BLINKING;
    }
    else if (arg == "BUTTON_PRESS")
    {
        mode = LedMode::BUTTON_PRESS;
    }
    else if (arg == "BUTTON_TOGGLE")
    {
        mode = LedMode::BUTTON_TOGGLE;
    }
    else
    {
        // Not a valid argument
        is_arg_valid = false;
    }

    if (is_arg_valid)
    {
        g_led.SetMode(mode);
    }

    return is_arg_valid;
}

static bool SetLedBlinkingPeriod_s(std::string_view arg)
{
    bool is_arg_valid = false;
    float period_s    = StrToFloat(arg, is_arg_valid);

    is_arg_valid &= period_s >= 0.0f;

    if (is_arg_valid)
    {
        g_led.SetBlinkingPeriod_s(period_s);
    }

    return is_arg_valid;
}

//---------------------------------------------------------------------------------------------------------------------
// PRIVATE VARIABLE DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

// clang-format off
// NOLINTNEXTLINE(*interfaces-global-init)
static std::array<CommandHookMap, 2> supported_commands{{
    {.name      = "set_led_mode",
     .hook_func = SetLedMode},
    {.name      = "set_led_blinking_period_s",
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

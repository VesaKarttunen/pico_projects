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

static bool SetLedMode(std::string_view mode_str)
{
    auto mode_enum = MapLedModeNameStrToEnum(mode_str);

    if (mode_enum.has_value())
    {
        g_led.SetMode(mode_enum.value());
        return true;
    }
    else
    {
        return false;
    }
}

static bool SetLedBlinkingPeriod_s(std::string_view period_str)
{
    auto period_s = ConvertStrToFloat(period_str);

    bool is_arg_valid = period_s.has_value()
                     && (period_s.value() >= 0.0f);

    if (is_arg_valid)
    {
        g_led.SetBlinkingPeriod_s(period_s.value());
    }

    return is_arg_valid;
}

//---------------------------------------------------------------------------------------------------------------------
// PRIVATE VARIABLE DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

// clang-format off
// NOLINTNEXTLINE(*interfaces-global-init)
static std::array<CommandHookMap, 2> f_supported_commands{{
    {.name      = "set_led_mode",
     .hook_func = SetLedMode},
    {.name      = "set_led_blinking_period_s",
     .hook_func = SetLedBlinkingPeriod_s}}};
// clang-format on

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC MEMBER FUNCTION DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

std::span<CommandHookMap> CommandConf::GetSupportedCommands()
{
    return f_supported_commands;
}

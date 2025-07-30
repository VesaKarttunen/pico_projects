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
// PRIVATE TYPE DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

struct LedModeMap
{
    std::string_view string;
    LedMode enum_val;
};

//---------------------------------------------------------------------------------------------------------------------
// PRIVATE CONSTANT DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

// clang-format off
static constexpr std::array<LedModeMap, 5> f_led_mode_map{
    {{.string = "ON",            .enum_val = LedMode::ON},
     {.string = "OFF",           .enum_val = LedMode::OFF},
     {.string = "BLINKING",      .enum_val = LedMode::BLINKING},
     {.string = "BUTTON_PRESS",  .enum_val = LedMode::BUTTON_PRESS},
     {.string = "BUTTON_TOGGLE", .enum_val = LedMode::BUTTON_TOGGLE}}
};
// clang-format on

//---------------------------------------------------------------------------------------------------------------------
// PRIVATE FUNCTION DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

static bool SetLedMode(std::string_view arg)
{
    for (auto mode : f_led_mode_map)
    {
        if (mode.string == arg)
        {
            g_led.SetMode(mode.enum_val);

            // Valid mode was found, thus search can be ended with early return
            return true;
        }
    }

    // Did not find valid mode corresponding the arg
    return false;
}

static bool SetLedBlinkingPeriod_s(std::string_view arg)
{
    auto period_s = ConvertStrToFloat(arg);

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

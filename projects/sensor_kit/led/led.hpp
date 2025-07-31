//---------------------------------------------------------------------------------------------------------------------
// LED
//---------------------------------------------------------------------------------------------------------------------

#pragma once

// STD
#include <array>
#include <optional>
#include <string_view>
#include <utility>

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC TYPE DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

enum struct LedMode
{
    OFF           = 0,
    ON            = 1,
    BLINKING      = 2,
    BUTTON_PRESS  = 3,
    BUTTON_TOGGLE = 4
};

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC FUNCTION DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

inline constexpr std::optional<LedMode> MapLedModeNameStrToEnum(std::string_view name)
{
    // clang-format off
    constexpr std::array<std::pair<std::string_view, LedMode>, 5> map_name_enum{{
        {"OFF",           LedMode::OFF},
        {"ON",            LedMode::ON},
        {"BLINKING",      LedMode::BLINKING},
        {"BUTTON_PRESS",  LedMode::BUTTON_PRESS},
        {"BUTTON_TOGGLE", LedMode::BUTTON_TOGGLE}}};
    // clang-format on

    for (auto [valid_name, mapped_enum] : map_name_enum)
    {
        if (name == valid_name)
        {
            return mapped_enum;
        }
    }

    return {};
}

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC CLASS DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

class Led
{
  public:
    static void Init();
    void SetMode(LedMode mode);
    void SetBlinkingPeriod_s(float period_s);
    void TaskPeriodic_100ms();

  private:
    LedMode m_mode            = LedMode::BLINKING;
    bool m_led_state          = false;
    float m_timer_s           = 0.0f;
    float m_blinking_period_s = 1.0f;
};

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC VARIABLE DECLARATIONS
//---------------------------------------------------------------------------------------------------------------------

extern Led g_led;

#pragma once

enum struct LedMode
{
    OFF           = 0,
    ON            = 1,
    BLINKING      = 2,
    BUTTON_PRESS  = 3,
    BUTTON_TOGGLE = 4
};

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

extern Led g_led;

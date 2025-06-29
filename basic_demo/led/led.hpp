#pragma once

enum struct LedMode
{
    OFF      = 0,
    ON       = 1,
    BLINKING = 2
};

class Led
{
  public:
    void SetLedMode(LedMode mode);
    void SetBlinkingPeriod_s(float period_s);
    void TaskPeriodic_100ms();

  private:
    LedMode m_mode      = LedMode::BLINKING;
    bool m_toggle       = false;
    int m_counter       = 0;
    int m_counter_limit = 20;
};

extern Led g_led;

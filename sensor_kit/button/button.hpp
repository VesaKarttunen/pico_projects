#pragma once

class Button
{
  public:
    static void Init();
    static bool IsPressed();
    bool Toggle();

  private:
    bool m_previous_state = false;
    bool m_toggled_state  = false;
};

extern Button g_button;

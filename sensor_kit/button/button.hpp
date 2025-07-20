#pragma once

class Button
{
  public:
    static void Init();
    static bool IsPressed();
    bool IsPressRisingEdge();

  private:
    bool m_was_pressed_previously = false;
};

extern Button g_button;

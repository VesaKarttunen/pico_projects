#pragma once

struct FeedbackFrame
{
    float time_stamp_s;
    float pcb_temperature_C;
};

class AppFeedback
{
  public:
    static FeedbackFrame GetData();
};

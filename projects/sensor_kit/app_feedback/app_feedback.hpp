//---------------------------------------------------------------------------------------------------------------------
// Application Feedback
//---------------------------------------------------------------------------------------------------------------------

#pragma once

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC TYPE DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

struct FeedbackFrame
{
    float time_stamp_s;
    float pcb_temperature_C;
};

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC CLASS DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

class AppFeedback
{
  public:
    static FeedbackFrame GetData();
};

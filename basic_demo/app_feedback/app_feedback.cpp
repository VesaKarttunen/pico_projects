// Own
#include "app_feedback.hpp"

// Local project
#include "temperature/temperature.hpp"

static constexpr float time_feedback_period_s = 1.0f;

FeedbackFrame AppFeedback::GetData()
{
    static float time_stamp_s;
    time_stamp_s += time_feedback_period_s;

    FeedbackFrame feedback_frame{
        .time_stamp_s      = time_stamp_s,
        .pcb_temperature_C = Temperature::GetPcbTemperature_C()};

    return feedback_frame;
}

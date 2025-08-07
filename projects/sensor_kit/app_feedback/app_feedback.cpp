//---------------------------------------------------------------------------------------------------------------------
// Application Feedback
//---------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------
// PRIVATE INCLUDE DIRECTIVES
//---------------------------------------------------------------------------------------------------------------------

// Own
#include "app_feedback.hpp"

// Local project
#include "temperature/temperature.hpp"

// STD
#include <cmath>
#include <numbers>

//---------------------------------------------------------------------------------------------------------------------
// PRIVATE CONSTANT DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

static constexpr float f_time_feedback_period_s = 1.0e-3f;

//---------------------------------------------------------------------------------------------------------------------
// PRIVATE VARIABLE DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

static FeedbackBuffer feedback_buffer;

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC MEMBER FUNCTION DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

const FeedbackBuffer& AppFeedback::GetData()
{
    static float time_stamp_s;
    for (FeedbackFrame& buffer_frame : feedback_buffer)
    {
        time_stamp_s += f_time_feedback_period_s;

        FeedbackFrame frame = {};
        frame.time_stamp_s  = time_stamp_s;

        float frequency_hz = 0.2f;
        float phase_rad    = 0.0f;
        float amplitude    = 1.0f;

        for (float& signal : frame.signals)
        {
            float angular_frequency_rad_s = 2.0f * std::numbers::pi_v<float> * frequency_hz;
            float angle_rad               = (angular_frequency_rad_s * time_stamp_s) + phase_rad;

            signal = amplitude * std::sin(angle_rad);

            // Create some variation for fake signals values
            phase_rad    += 0.5f;
            frequency_hz += 0.2f;
            amplitude    += 0.5f;
        }

        buffer_frame = frame;
    }

    return feedback_buffer;
}

//---------------------------------------------------------------------------------------------------------------------
// String Conversion Helper Functions
//---------------------------------------------------------------------------------------------------------------------

#pragma once

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC INCLUDE DIRECTIVES
//---------------------------------------------------------------------------------------------------------------------

// STD
#include <charconv>
#include <string_view>

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC FUNCTION DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

inline float StrToFloat(std::string_view string, bool& is_success)
{
    const char* begin = string.data();
    const char* end   = string.data() + string.length();

    float output = 0.0f;
    auto status  = std::from_chars(begin, end, output);

    // Success if no error codes and the conversion reached the end of the string_view
    is_success = (status.ec == std::errc{})
              && (status.ptr == end);

    return output;
}

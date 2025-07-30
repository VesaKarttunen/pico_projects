//---------------------------------------------------------------------------------------------------------------------
// String Conversion Helper Functions
//---------------------------------------------------------------------------------------------------------------------

#pragma once

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC INCLUDE DIRECTIVES
//---------------------------------------------------------------------------------------------------------------------

// STD
#include <charconv>
#include <optional>
#include <string_view>

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC FUNCTION DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

inline std::optional<float> ConvertStrToFloat(std::string_view string)
{
    const char* begin = string.data();
    const char* end   = string.data() + string.length();

    float output = 0.0f;
    auto status  = std::from_chars(begin, end, output);

    // Success if no error codes and the conversion reached the end of the string_view
    bool is_success = (status.ec == std::errc{})
                   && (status.ptr == end);

    if (is_success)
    {
        return output;
    }
    else
    {
        // Conversion failed. Indicate error by returning empty value.
        return {};
    }
}

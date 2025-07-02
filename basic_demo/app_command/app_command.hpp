#pragma once

#include <array>
#include <string_view>

struct CommandFrame
{
    std::array<char, 64> name;
    float arqument;
};

class AppCommand
{
  public:
    static void ProcessCommand(const CommandFrame& requested_command);
};

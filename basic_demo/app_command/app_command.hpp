#pragma once

#include <array>

struct CommandFrame
{
    std::array<char, 64> name;
    float argument;
};

class AppCommand
{
  public:
    static void ProcessCommand(const CommandFrame& requested_command);
};

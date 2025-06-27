#pragma once

#include <string_view>

class AppCommand
{
  public:
    static void ProcessCommand(std::string_view command);
};

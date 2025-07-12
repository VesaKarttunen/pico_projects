// STD
#include <span>
#include <string_view>

using CommandHookFunc = void (&)(float);

struct CommandHookMap
{
    std::string_view name;
    CommandHookFunc hook_func; // NOLINT(*ref-data-members)
};

class CommandConf
{
  public:
    static std::span<CommandHookMap> GetSupportedCommands();
};

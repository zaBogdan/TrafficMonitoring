#include "sourceCommands.h"

std::string BTruckers::Server::Commands::Craft::SetSettings(std::string payload)
{
    return std::string(SETSETTINGS_COMMAND) +":"+payload;
}

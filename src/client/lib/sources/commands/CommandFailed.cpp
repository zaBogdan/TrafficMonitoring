#include "sourceCommands.h"

std::string BTruckers::Client::Commands::Handle::CommandFailed(std::string payload)
{
    return PrimiteTypes::FromString(payload).value;
}
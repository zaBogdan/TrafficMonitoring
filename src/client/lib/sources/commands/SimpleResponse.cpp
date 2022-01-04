#include "clientCommands.h"

std::string BTruckers::Client::Commands::Handle::SimpleResponse(std::string payload)
{
    return PrimiteTypes::FromString(payload).value;
}
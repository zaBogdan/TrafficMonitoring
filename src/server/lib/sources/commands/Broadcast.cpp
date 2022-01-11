#include "sourceCommands.h"

std::string BTruckers::Server::Commands::Craft::Broadcast(std::string payload)
{
    payload = PrimiteTypes::ToString(payload);
    std::string command = std::string(SUCCESSRESPONSE_COMMAND) + std::string(":") + payload;

    return "hello";
}
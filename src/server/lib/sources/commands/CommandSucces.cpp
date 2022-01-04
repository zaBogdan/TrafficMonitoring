#include "sourceCommands.h"

// SUCCESSRESPONSE_COMMAND
std::string BTruckers::Server::Commands::Craft::CommandSuccess(std::string payload)
{
    payload = PrimiteTypes::ToString(payload);
    std::string command = std::string(SUCCESSRESPONSE_COMMAND) + std::string(":") + payload;
    return command;
}
#include "sourceCommands.h"

// FAILEDRESPONSE_COMMAND
std::string BTruckers::Server::Commands::Craft::CommandFailed(std::string payload)
{
    payload = PrimiteTypes::ToString(payload);
    std::string command = std::string(FAILEDRESPONSE_COMMAND) + std::string(":") + payload;
    LOG_DEBUG("Failed due to: %s", command.c_str());
    return command;
}
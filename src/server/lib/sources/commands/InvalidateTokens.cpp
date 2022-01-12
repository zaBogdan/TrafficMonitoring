#include "sourceCommands.h"

std::string BTruckers::Server::Commands::Craft::InvalidateTokens(std::string payload)
{
    std::string command = std::string(INVALIDATETOKENS_COMMAND) + ":" + payload;

    return command;
}
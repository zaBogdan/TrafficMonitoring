#include "sourceCommands.h"

std::string BTruckers::Server::Commands::Handle::ChangeOption(BTruckers::Server::Core::DBHandler *db,std::string payload)
{
    payload = PrimiteTypes::FromDict(payload);

    return BTruckers::Server::Commands::Craft::SetSettings(payload);
}
#include "sourceCommands.h"

std::string BTruckers::Client::Commands::Handler(BTruckers::Shared::Structures::Message message)
{
    return message.payload;
}
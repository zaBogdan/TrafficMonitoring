#include "clientCommands.h"

std::string BTruckers::Client::Commands::Craft::GetSettings(std::string payload)
{
    payload = payload;
    //finally build the command 
    std::string command = std::string(GETSETTINGS_COMMAND) + ":" + PrimiteTypes::ToString("all");
    //and that's the end.
    return command;
}
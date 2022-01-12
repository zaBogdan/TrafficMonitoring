#include "clientCommands.h"

std::string BTruckers::Client::Commands::Craft::Logout(std::string payload)
{
    payload = payload;
    //finally build the command 
    std::string command = std::string(LOGOUT_COMMAND) + ":" + PrimiteTypes::ToString("Bye");
    //and that's the end.
    return command;
}
#include "clientCommands.h"

std::string BTruckers::Client::Commands::Craft::SwitchPreference(std::string cmd, std::string payload)
{
    std::string value = "0";
    if(cmd == "enable")
    {
        value = "1";
    }
    std::string command = std::string(PREFERENCE_COMMAND) + ":" + PrimiteTypes::ToString(value, payload);
    //and that's the end.
    return command;
}
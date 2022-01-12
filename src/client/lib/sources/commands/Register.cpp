#include "clientCommands.h"

std::string BTruckers::Client::Commands::Craft::Register(std::string payload)
{
    size_t splitPosition = payload.find(" ");
    std::vector<std::string> parameters;
    
    while(splitPosition != std::string::npos)
    {
        parameters.push_back(payload.substr(0, splitPosition));
        payload = payload.substr(splitPosition+1);
        splitPosition = payload.find(" ");
    }

    parameters.push_back(payload);

    //setting the fields
    parameters[0] = PrimiteTypes::ToString(parameters[0], "username");
    parameters[1] = PrimiteTypes::ToString(parameters[1], "password");
    parameters[2] = PrimiteTypes::ToString(parameters[2], "firstname");
    parameters[3] = PrimiteTypes::ToString(parameters[3], "lastname");
    parameters[4] = PrimiteTypes::ToString(parameters[4], "company");
    parameters[5] = PrimiteTypes::ToString(parameters[5], "email");

    //finally build the command 
    std::string command = std::string(REGISTER_COMMAND) + std::string(":") + PrimiteTypes::ToDict(parameters);

    //and that's the end.
    return command;
}
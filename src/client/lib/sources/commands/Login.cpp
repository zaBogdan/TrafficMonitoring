#include "sourceCommands.h"

std::string BTruckers::Client::Commands::Craft::Authentication(std::string payload)
{
    size_t splitPosition = payload.find(":");

    //if the payload can't be splitted we will just return
    if(splitPosition == std::string::npos)
        return "";

    //splitting them
    std::string username = payload.substr(0, splitPosition);
    std::string password = payload.substr(splitPosition+1);

    //transforming to string
    username = PrimiteTypes::ToString(username, "username");
    password = PrimiteTypes::ToString(password, "password");

    //getting the dictionary
    std::vector<std::string> finalDict {username, password};
    std::string dict = PrimiteTypes::ToDict(finalDict);

    //finally build the command 
    std::string command = std::string(AUTHENTICATE_COMMAND) + std::string(":") + dict;

    //and that's the end.
    return command;
}
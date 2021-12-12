#include "sourceCommands.h"
#define COMMAND_NAME "Authenticate"

std::string BTRShared::Command::CreateAuthenticateCommand(std::string payload)
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

    printf("Username: '%s', password: '%s'\n", username.c_str(), password.c_str());
    
    //getting the dictionary
    std::vector<std::string> finalDict {username, password};
    std::string dict = PrimiteTypes::ToDict(finalDict, "hello");

    //finally build the command 
    std::string command = std::string(COMMAND_NAME) + std::string(":") + dict;

    //and that's the end.
    return command;
}

std::string BTRShared::Command::ParseAuthenticateCommand(std::string payload)
{
    //to be implemented
    return payload;
}
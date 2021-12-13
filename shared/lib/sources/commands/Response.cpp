#include "sharedCommands.h"
#define COMMAND_NAME "Response"

std::string BTRShared::Command::CreateResponseCommand(std::string payload)
{
    printf("Create response\n");

    //and that's the end.
    return payload;
}

std::string BTRShared::Command::ParseResponseCommand(std::string payload)
{
    //to be implemented
    return payload;
}
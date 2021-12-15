#include "sourceCommands.h"
#define COMMAND_NAME "Authenticate"

std::string BTrucks::Commands::HandleValidateTokensCommand(std::string payload)
{
    std::vector<BTRShared::Utils::KeyValue> loginCredentials = PrimiteTypes::FromDict(payload);
    printf("[Credentials] Username: %s\n", loginCredentials[0].value.c_str());
    printf("[Credentials] Password: %s\n", loginCredentials[1].value.c_str());
    //to be implemented the logic
    return "sSuccessfully logged in";
}
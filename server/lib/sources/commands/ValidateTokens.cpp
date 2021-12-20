#include "sourceCommands.h"
#define COMMAND_NAME "Authenticate"


std::string BTruckers::Server::Commands::HandleValidateTokensCommand(std::string payload)
{
    std::vector<BTruckers::Shared::Structures::KeyValue> loginCredentials = PrimiteTypes::FromDict(payload);
    printf("[Credentials] Username: %s\n", loginCredentials[0].value.c_str());
    printf("[Credentials] Password: %s\n", loginCredentials[1].value.c_str());
    //to be implemented the logic
    return "sSuccessfully logged in";
}
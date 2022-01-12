#include "sourceCommands.h"

std::string BTruckers::Server::Commands::Handle::Logout(BTruckers::Server::Core::DBHandler *db,std::string payload)
{
    BTruckers::Server::Models::Tokens token (db, "identifier", payload);

    //if we can't find them we just return the command to client
    if(token.GetField("uuid") == "")
        return BTruckers::Server::Commands::Craft::InvalidateTokens(payload);
    
    //otherwise delete + invalidate
    token.Delete();
    return BTruckers::Server::Commands::Craft::InvalidateTokens(payload);
}
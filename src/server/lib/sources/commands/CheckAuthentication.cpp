#include "sourceCommands.h"


uint32_t BTruckers::Server::Commands::CheckAuthentication(BTruckers::Shared::Structures::Message message, BTruckers::Server::Core::DBHandler *db, BTruckers::Server::Models::Users *user)
{
    uint32_t crcValue = BTruckers::Shared::Utils::CRCValue(message.command);

    for(auto route : BTruckers::Server::Commands::publicRoutes)
    {
        if(crcValue == route)
            return crcValue;
    }

    //checking for tokens
    if(message.token.identifier == "" || message.token.validator == "")
        return 0;


    BTruckers::Server::Models::Tokens token (db, "identifier", message.token.identifier);
    token.Print();

    //validating that the retrived token is ok
    if(token.GetField("identifier") != message.token.identifier)
        return 0;

    //checking the validator
    if(!token.VerifyToken(message.token.validator))
        return 0;

    user->FindBy("uuid", token.GetField("user_uuid"));
        
    return crcValue;
}
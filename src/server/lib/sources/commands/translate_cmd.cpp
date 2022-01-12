#include "sourceCommands.h"


std::string BTruckers::Server::Commands::Handler(BTruckers::Shared::Structures::Message& message, BTruckers::Server::Core::DBHandler* db)
{
    if(!message.success)
        return BTruckers::Server::Commands::Craft::CommandFailed("Command with invalid syntax.");

    BTruckers::Server::Models::Users user(db);
    
    uint32_t crcValue = BTruckers::Server::Commands::CheckAuthentication(message, db, &user);

    //checking authentication 
    if(!crcValue)
    {
        return BTruckers::Server::Commands::Craft::CommandFailed("You need to be authenticated to use this route.");
    }
    
    LOG_INFO("Handling command '%s' with the crcValue: 0x%X", message.command.c_str(), crcValue);
    
    std::string response = "";
    switch(crcValue)
    {
        case BTruckers::Server::Enums::CommandsCRC::AUTHENTICATE:
            response = BTruckers::Server::Commands::Handle::Authentication(db, message.payload);
            break;
        
        case BTruckers::Server::Enums::CommandsCRC::INCIDENT:
            response = BTruckers::Server::Commands::Handle::Incident(db,&user, message.payload);
            break;

        case BTruckers::Server::Enums::CommandsCRC::BROADCAST:
            //extra safety check (to be sure users will not be able to broadcast)
            if(message.token.validator != APPLICATION_SECRET)
                break;
            response = BTruckers::Server::Commands::Craft::Broadcast(message.payload);
            break;

        default:
            response = BTruckers::Server::Commands::Craft::CommandFailed("Command doesn't exist.");
    }

    //just an error checking
    if(response == "")
    {
        LOG_ERROR("Something went wrong... setting the response to failed just in case");
        return BTruckers::Server::Commands::Craft::CommandFailed("Something went wrong.");
    }

    message.userUUID = user.GetField("uuid");

    LOG_DEBUG("The response for the command is: %s", response.c_str());
    return response;
}
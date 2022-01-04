#include "sourceCommands.h"


std::string BTruckers::Server::Commands::Handler(BTruckers::Shared::Structures::Message message, BTruckers::Server::Core::DBHandler* db)
{
    if(!message.success)
        return BTruckers::Server::Commands::Craft::CommandFailed("Command with invalid syntax.");


    
    uint32_t crcValue = BTruckers::Server::Commands::CheckAuthentication(message, db);
    //checking if the user needs to be authenticated 
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
            response = BTruckers::Server::Commands::Handle::Incident(db, message.payload);
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

    LOG_DEBUG("The response for the command is: %s", response.c_str());
    return response;
}
#include "sourceCommands.h"

std::string BTruckers::Server::Commands::Handler(BTruckers::Shared::Structures::Message message, BTruckers::Server::Core::DBHandler* db)
{
    if(!message.success)
        return "fCommand with invalid syntax.";

    uint32_t crcValue = BTruckers::Shared::Utils::CRCValue(message.command);

    message.print();
    LOG_INFO("Handling command '%s' with the crcValue: 0x%x", message.command.c_str(), crcValue);
    
    //here I should check if the crcValue is in the list of "public" commands
    //todo
        // return "fYou need to be authenticated to use this route.";

    std::string response = "";
    switch(crcValue)
    {
        case BTruckers::Server::Enums::CommandsCRC::AUTHENTICATE:
            response = BTruckers::Server::Commands::Handle::Authentication(db, message.payload);
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
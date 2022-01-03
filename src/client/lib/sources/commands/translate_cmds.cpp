#include "sourceCommands.h"

std::string BTruckers::Client::Commands::HandleResponse(BTruckers::Shared::Structures::Message message)
{
    if(!message.success)
    {
        LOG_ERROR("There was something wrong with the response message.");
        return "";
    }

    uint32_t crcValue = BTruckers::Shared::Utils::CRCValue(message.command);
    
    std::string response = "";

    LOG_INFO("Handling command '%s' with the crcValue: 0x%X", message.command.c_str(), crcValue);

    switch(crcValue)
    {
        case BTruckers::Client::Enums::CommandsCRC::AUTH:
        case BTruckers::Client::Enums::CommandsCRC::AUTHENTICATE:
        case BTruckers::Client::Enums::CommandsCRC::LOGIN:
            response = BTruckers::Client::Commands::Craft::Authentication(message.payload);
            break;
        case BTruckers::Client::Enums::CommandsCRC::SETTOKEN:
            response = BTruckers::Client::Commands::Handle::SetTokens(message.payload);
            break;

        default:
            LOG_ERROR("Command doesn't exist yet. Check your spelling.");
            response = "";
    }

    return response;
}
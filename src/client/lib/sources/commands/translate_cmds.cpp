#include "clientCommands.h"

std::string BTruckers::Client::Commands::HandleResponse(BTruckers::Shared::Structures::Message message, bool isRequest)
{
    if(!message.success)
    {
        LOG_ERROR("There was something wrong with the response message.");
        return "";
    }
    uint32_t crcValue = BTruckers::Shared::Utils::CRCValue(message.command);
    
    std::string response = "";

    LOG_DEBUG("Handling command '%s' with the crcValue: 0x%X", message.command.c_str(), crcValue);

    switch(crcValue)
    {
        case BTruckers::Client::Enums::CommandsCRC::AUTH:
        case BTruckers::Client::Enums::CommandsCRC::AUTHENTICATE:
        case BTruckers::Client::Enums::CommandsCRC::LOGIN:
            response = BTruckers::Client::Commands::Craft::Authentication(message.payload);
            break;

        case BTruckers::Client::Enums::CommandsCRC::REGISTER:
            response = BTruckers::Client::Commands::Craft::Register(message.payload);
            break;

        case BTruckers::Client::Enums::CommandsCRC::INCIDENT:
            response = BTruckers::Client::Commands::Craft::ReportIncident(message.payload);
            break;
        
        case BTruckers::Client::Enums::CommandsCRC::METRICS:
            response = BTruckers::Client::Commands::Craft::SendMetrics(message.payload);
            break;
            
        case BTruckers::Client::Enums::CommandsCRC::SETTOKEN:
            response = BTruckers::Client::Commands::Handle::SetTokens(message.payload);
            break;

        case BTruckers::Client::Enums::CommandsCRC::BROADCAST:
            response = BTruckers::Client::Commands::Handle::Broadcast(message.payload);
            break;

        case BTruckers::Client::Enums::CommandsCRC::LOGOUT:
            response = BTruckers::Client::Commands::Craft::Logout(message.payload);
            break;

        case BTruckers::Client::Enums::CommandsCRC::INVALIDATETOKENS:
            response = BTruckers::Client::Commands::Handle::InvalidateTokens(message.payload);
            break;

        case BTruckers::Client::Enums::CommandsCRC::ENABLE_PREFERANCE:
        case BTruckers::Client::Enums::CommandsCRC::DISABLE_PREFERANCE:
            response = BTruckers::Client::Commands::Craft::SwitchPreference(message.command,message.payload);
            break;

        case BTruckers::Client::Enums::CommandsCRC::HELP:
            response = BTruckers::Client::Commands::Craft::Help(message.payload);
            break;

        case BTruckers::Client::Enums::CommandsCRC::RESTORE:
            response = BTruckers::Client::Commands::Craft::GetSettings(message.payload);
            break;

        case BTruckers::Client::Enums::CommandsCRC::SETSETTINGS:
            response = BTruckers::Client::Commands::Handle::SetSettings(message.payload);
            break;
        
        case BTruckers::Client::Enums::CommandsCRC::VIEW_SETTINGS:
            response = BTruckers::Client::Commands::Craft::ViewSettings(message.payload);
            break;

        case BTruckers::Client::Enums::CommandsCRC::FAILEDCOMMAND:
        case BTruckers::Client::Enums::CommandsCRC::SUCCESSCOMMAND:
            response = BTruckers::Client::Commands::Handle::SimpleResponse(message.payload);
            break;


        default:
            LOG_ERROR("Command doesn't exist yet. Check your spelling.");
            response = "";
    }
    if(response == "Help")
        return response;
    if(isRequest && response != "")
    {
        //here I will add the tokens if they are set.
        if(message.token.identifier != "" && message.token.validator != "")
        {
            response = message.token.identifier + ":" + message.token.validator+ "|" + response;
        }
    }
    LOG_DEBUG("The response is: %s", response.c_str());
    return response;
}
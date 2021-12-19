#include "Command.h"


std::string BTruckers::Client::Handler::Create(std::string command, std::string token)
{
    //getting the position between command and payload
    size_t spaceFind = command.find(" ");

    //splitting them
    std::string userCmd = command.substr(0, spaceFind);
    std::string payload = command.substr(spaceFind+1);
    
    //Doing some normalization:
    for(auto& c : userCmd)
    {
        c = tolower(c);
    }

    LOG_DEBUG("Token is: %s", token.c_str());
    
    // now we should handle each command with their ruleset.  Calculating crc
    uint32_t crcValue = BTruckers::Shared::Utils::CRCValue(userCmd);

    LOG_INFO("Handling command '%s' with the crcValue: 0x%x", userCmd.c_str(), crcValue);

    //getting the right handler
    switch(crcValue)
    {
        case BTruckers::Client::Enums::CommandsCRC::AUTH:
        case BTruckers::Client::Enums::CommandsCRC::AUTHENTICATE:
        case BTruckers::Client::Enums::CommandsCRC::LOGIN:
            return BTruckers::Client::Commands::CreateAuthenticateCommand(payload);
            
        case BTruckers::Client::Enums::CommandsCRC::INCIDENT:
            return BTruckers::Client::Commands::CreateIncidentCommand(payload);
        
        case BTruckers::Shared::Enums::CommandsCRC::RESPONSE:
            return BTruckers::Shared::Commands::CreateResponseCommand(payload);
        default:
            LOG_ERROR("Command not found. Make sure you spelled it correctly.");
            return "";
    }
}
#include "CPV.h"

std::string BTruckers::Client::Core::CPV::Craft(std::string Payload)
{
    //getting the position between command and payload
    size_t spaceFind = Payload.find(" ");

    //splitting them
    std::string userCmd = Payload.substr(0, spaceFind);
    std::string payload = Payload.substr(spaceFind+1);
    
    //Doing some normalization:
    for(auto& c : userCmd)
    {
        c = tolower(c);
    }

    // here i will get the token from the internal state class
    // LOG_DEBUG("Token is: %s", token.c_str());
    
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

BTruckers::Shared::Structures::Message BTruckers::Client::Core::CPV::Parse(std::string payload)
{
    LOG_DEBUG("The payload to parse is: %s", payload.c_str())
    BTruckers::Shared::Structures::Message data;
    return data;
}

bool BTruckers::Client::Core::CPV::Validate(std::string payload)
{
    LOG_DEBUG("The payload to validate is: %s", payload.c_str())

    return false;
}
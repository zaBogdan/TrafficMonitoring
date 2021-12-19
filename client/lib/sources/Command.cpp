#include "Command.h"


std::string BTrucks::CommandHandler::Create(std::string command, std::string token)
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

    // now we should handle each command with their ruleset.  Calculating crc
    uint32_t crcValue = BTRShared::Utils::CRCValue(userCmd);

    LOG_INFO("Handling command '%s' with the crcValue: 0x%x", userCmd.c_str(), crcValue);

    //getting the right handler
    switch(crcValue)
    {
        case BTrucks::Utils::Command::AUTH:
        case BTrucks::Utils::Command::AUTHENTICATE:
        case BTrucks::Utils::Command::LOGIN:
            return BTrucks::Commands::CreateAuthenticateCommand(payload);
            
        case BTrucks::Utils::Command::INCIDENT:
            return BTrucks::Commands::CreateIncidentCommand(payload);
        
        case BTRShared::Utils::Command::RESPONSE:
            return BTRShared::Command::CreateResponseCommand(payload);
        default:
            LOG_ERROR("Command not found. Make sure you spelled it correctly.");
            return "";
    }
}
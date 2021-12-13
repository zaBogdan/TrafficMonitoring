#include "Command.h"


std::string BTrucks::CommandHandler::Evaluate(std::string command, std::string token)
{
    Logger::Debug("[EVALUATE] Starting to check the command.");
    printf("command is: %s\n", command.c_str());
    
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

    printf("userCmd is: '%s' and payload is: '%s'\n", userCmd.c_str(),payload.c_str());
    // now we should handle each command with their ruleset.  Calculating crc
    uint32_t crcValue = BTRShared::Utils::CRCValue(userCmd);


    printf("The command '%s' hash the crcValue: 0x%x\n",userCmd.c_str(),crcValue);

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
            Logger::Error("Command doesn't exist yet. Check the spelling.");
            return "";
    }
}
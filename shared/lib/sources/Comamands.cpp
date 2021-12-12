#include "Commands.h"


std::string BTRShared::Commands::HandleCommand(const char* command, const char* payload)
{
    Logger::Debug("Starting to check the command to send to parser");
    printf("%s , %s", command, payload);
    return "";
}

std::string BTRShared::Commands::Evaluate(std::string command)
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


    printf("The command %s hash the crcValue: 0x%x\n",userCmd.c_str(),crcValue);

    switch(crcValue)
    {
        case BTRShared::Utils::CommandsCRC::AUTH:
        case BTRShared::Utils::CommandsCRC::AUTHENTICATE:
        case BTRShared::Utils::CommandsCRC::LOGIN:
            return BTRShared::Command::CreateAuthenticateCommand(payload);
            
        case BTRShared::Utils::CommandsCRC::INCIDENT:
            return BTRShared::Command::CreateIncidentCommand(payload);
        
        default:
            Logger::Error("Command doesn't exist yet. Check the spelling.");
            return "";
    }
}
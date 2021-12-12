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
    printf("command is: %s", command.c_str());
    // uint32_t crcValue = BTRShared::Utils::CRCValue(command.c_str(), command.length())
    // Logger::Debug("[EVALUATE] CrcValue:");
    // printf("0x%x\n", BTRShared::Utils::CRCValue(command.c_str(), command.length()));
    // Logger::Debug("[EVALUATE] Starting other shit now");





    return "Authenticate:d{suser:zaBogdan,spassword:P@ssw0rd1}";
}
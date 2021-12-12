#include "sourceCommands.h"

std::string BTRShared::Command::CreateAuthenticateCommand(std::string payload)
{
    return "Authenticate:d{suser:zaBogdan,spassword:P@ssw0rd1}";
}

std::string BTRShared::Command::ParseAuthenticateCommand(std::string payload)
{
    //to be implemented
    return "";
}
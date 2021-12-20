#include "Command.h"


std::string BTruckers::Server::Handler::Handle(std::string command)
{
    BTruckers::Shared::Structures::Message message = Message::Parse(command);
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
            response = BTruckers::Server::Commands::HandleAuthenticateCommand(message.payload);
            break;

        default:
            return "fCommand doesn't exist.";
    }
    return response;
}

#include "Message.h"

Message *Message::instance = 0;

Message::Message()
{

}

Message* Message::GetInstance()
{
    if(!instance)
        instance = new Message;
    return instance;
}

std::string Message::Format(std::string formatedMessage)
{
    if(formatedMessage == "")
    {
        return "";
    }
    
    formatedMessage = MESSAGE_SEPARATOR + formatedMessage;
    
    //prefixing the message with it's length
    std::string messageLength = std::to_string(formatedMessage.length());
    messageLength.insert(0, 4-messageLength.length(),'0');
    formatedMessage = messageLength+formatedMessage;

    //returning the message
    return formatedMessage;
}


BTruckers::Shared::Structures::Message Message::Parse(std:: string command)
{
    BTruckers::Shared::Structures::Message msg;
    if(command[0] != MESSAGE_SEPARATOR[0])
    {
        LOG_ERROR("Message syntax is invalid");
        return msg;
    }

    size_t lastSeparatorPosition = command.find_last_of(MESSAGE_SEPARATOR);
    if(lastSeparatorPosition == std::string::npos)
    {
        LOG_ERROR("Message syntax is invalid");
        return msg;
    }

    if(lastSeparatorPosition != 0)
    {
        LOG_DEBUG("Starting to parse the tokens");
        // std::string tokens = 
        //trim the string also to be formated right and leave it |Command
    }

    //remove the |
    command = command.substr(1);

    size_t splitterLocation  = command.find(TYPE_SEPARATOR);
    if(splitterLocation == std::string::npos)
    {
        LOG_ERROR("Message syntax is invalid");
        return msg;
    }

    //splitting them into the right values
    msg.command = command.substr(0, splitterLocation);
    for(auto &x : msg.command)
    {
        x = std::tolower(x);
    }
    msg.payload = command.substr(splitterLocation+1);
    msg.success = true;
    return msg;
}

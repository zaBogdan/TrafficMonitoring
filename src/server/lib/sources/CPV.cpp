#include "CPV.h"

BTruckers::Shared::Structures::Message BTruckers::Server::Core::CPV::Craft(std::string Payload)
{
    BTruckers::Shared::Structures::Message data;
    LOG_DEBUG("The payload to be crafted is: %s", Payload.c_str())
    return data;
}

BTruckers::Shared::Structures::Message BTruckers::Server::Core::CPV::Parse(std::string payload)
{
    BTruckers::Shared::Structures::Message msg;
    if(payload[0] != MESSAGE_SEPARATOR[0])
    {
        LOG_ERROR("Message syntax is invalid");
        return msg;
    }

    size_t lastSeparatorPosition = payload.find_last_of(MESSAGE_SEPARATOR);
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
    payload = payload.substr(1);

    size_t splitterLocation  = payload.find(TYPE_SEPARATOR);
    if(splitterLocation == std::string::npos)
    {
        LOG_ERROR("Message syntax is invalid");
        return msg;
    }

    //splitting them into the right values
    msg.command = payload.substr(0, splitterLocation);
    for(auto &x : msg.command)
    {
        x = std::tolower(x);
    }
    msg.payload = payload.substr(splitterLocation+1);
    msg.success = true;
    return msg;
}

bool BTruckers::Server::Core::CPV::Validate(std::string payload)
{
    LOG_DEBUG("The payload to validate is: %s", payload.c_str())

    return false;
}
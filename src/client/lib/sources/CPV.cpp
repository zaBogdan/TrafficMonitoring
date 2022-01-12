#include "CPV.h"

BTruckers::Shared::Structures::Message BTruckers::Client::Core::CPV::Craft(std::string Payload)
{
    BTruckers::Shared::Structures::Message data;

    if(Payload == "")
        return data;
        
    //getting the position between command and payload
    size_t spaceFind = Payload.find(" ");

    //splitting them
    data.command = Payload.substr(0, spaceFind);
    data.payload = Payload.substr(spaceFind+1);
    
    //Doing some normalization:
    for(auto& c : data.command)
    {
        c = tolower(c);
    }

    // here i will get the token from the internal state class
    data.token.identifier = BTruckers::Client::Core::StorageBox::GetItem("identifier");
    data.token.validator = BTruckers::Client::Core::StorageBox::GetItem("validator");

    data.success = true;

    return data;
}

BTruckers::Shared::Structures::Message BTruckers::Client::Core::CPV::Parse(std::string payload)
{
    BTruckers::Shared::Structures::Message data;
    if(payload == "")
        return data;

    payload = payload.substr(1);
    size_t splitPosition = payload.find(":");

    if(splitPosition == std::string::npos)
    {
        LOG_ERROR("We've received an invalid payload: '%s'", payload.c_str());
        return data;
    }
    
    data.command = payload.substr(0, splitPosition);
    data.payload = payload.substr(splitPosition+1);

    data.success = true;

    return data;
}

bool BTruckers::Client::Core::CPV::Validate(std::string payload)
{
    LOG_DEBUG("The payload to validate is: %s", payload.c_str())

    return false;
}
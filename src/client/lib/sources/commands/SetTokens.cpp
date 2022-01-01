#include "sourceCommands.h"

std::string BTruckers::Client::Commands::Handle::SetTokens(std::string payload)
{
    std::vector<BTruckers::Shared::Structures::KeyValue> data = PrimiteTypes::FromDict(payload);
    std::string identifier = "", validator = "";
    
    //setting the values
    for(auto x : data)
    {
        if(x.key == "identifier")
        {
            identifier = x.value;
            continue;
        }
        if(x.key == "validator")
        {
            validator = x.value;
            continue;
        }
    }

    //checking the validity of data
    if(identifier == "" || validator == "")
    {
        LOG_ERROR("Failed to set the IDENTIFIER or the VALIDATOR.")
        return "Failed to handle";
    }
    BTruckers::Client::Core::StorageBox::SetItem("identifier", identifier);
    BTruckers::Client::Core::StorageBox::SetItem("validator", validator);

    if(DEBUG_MODE == true)
    {
        return "Successfully got the IDENTIFIER and the VALIDATOR. Successfully logged in.";
    }
    return "Successfully logged in.";
}
#include "clientCommands.h"

std::string BTruckers::Client::Commands::Handle::SetSettings(std::string payload)
{
    //finally build the command 
    std::vector<BTruckers::Shared::Structures::KeyValue> data = PrimiteTypes::FromDict(payload);
    for(auto _d : data)
    {
        BTruckers::Client::Core::StorageBox::SetItem(_d.key, _d.value);
    }

    BTruckers::Client::Core::StorageBox::DumpToFile();

    //and that's the end.
    return "Settings successfully set!";
}
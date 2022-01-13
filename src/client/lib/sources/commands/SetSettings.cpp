#include "clientCommands.h"

std::string BTruckers::Client::Commands::Handle::SetSettings(std::string payload)
{
    //finally build the command 
    BTruckers::Shared::Structures::KeyValue data = PrimiteTypes::FromString(payload);
    BTruckers::Client::Core::StorageBox::SetItem(data.key, data.value);

    BTruckers::Client::Core::StorageBox::DumpToFile();

    //and that's the end.
    return "Settings successfully set!";
}
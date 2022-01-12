#include "clientCommands.h"

std::string BTruckers::Client::Commands::Handle::InvalidateTokens(std::string payload)
{
    payload = payload;
    BTruckers::Client::Core::StorageBox::SetItem("identifier", "");
    BTruckers::Client::Core::StorageBox::SetItem("validator", "");
    //and that's the end.
    return "Successfully logged out!";
}
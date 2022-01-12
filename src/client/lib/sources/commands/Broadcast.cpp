#include "clientCommands.h"

std::string BTruckers::Client::Commands::Handle::Broadcast(std::string payload)
{
    std::vector<BTruckers::Shared::Structures::KeyValue> broadcastedMessages = PrimiteTypes::FromDict(payload);
    printf("\n-=-=-=-=-=-=-=-=-=-= BROADCAST =-=-=-=-=-=-=-=-=-=-\n");
    for(auto msg : broadcastedMessages)
    {
        // if(msg.key == "optional" && BTruckers::Client::Core::StorageBox::GetItem("optionalBroadcasts") == "")
        //     continue;
        if(msg.value == "")
            continue;
        printf("----> %s\n", msg.value.c_str());
    }
    printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
   return BROADCAST_COMMAND;
}
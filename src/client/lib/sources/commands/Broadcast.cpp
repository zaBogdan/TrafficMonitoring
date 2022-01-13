#include "clientCommands.h"

std::string BTruckers::Client::Commands::Handle::Broadcast(std::string payload)
{
    std::vector<BTruckers::Shared::Structures::KeyValue> broadcastedMessages = PrimiteTypes::FromDict(payload);
    int firstAdvertise = 0;
    for(auto msg : broadcastedMessages)
    {
        if(msg.key == "optional" && BTruckers::Client::Core::StorageBox::GetItem("media") != "1")
            continue;
        ++firstAdvertise;
        if(firstAdvertise == 1)
        {
            printf("\n-=-=-=-=-=-=-=-=-=-= BROADCAST =-=-=-=-=-=-=-=-=-=-\n");
        }
        if(msg.value == "")
            continue;
        printf("----> %s\n", msg.value.c_str());
    }
    if(firstAdvertise)
    {
        printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    }
   return BROADCAST_COMMAND;
}
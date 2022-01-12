#include "sourceCommands.h"

std::string BTruckers::Server::Commands::Craft::Broadcast(std::string payload)
{
    LOG_DEBUG("Payload is: %s", payload.c_str());
    std::vector<std::string> broadcastDict;
    size_t findPayload = 0;
    while(findPayload != std::string::npos)
    {
        findPayload = payload.find("|");
        broadcastDict.push_back(payload.substr(0, findPayload));
        payload.erase(0, findPayload+1);
    } 
    for(auto& strr : broadcastDict)
    {
        if(strr == "")
            continue;
        printf("str[0]=%d",strr[0] - '0');
        if((strr[0]-'0') == BTruckers::Server::Enums::BroadcastConditions::SELECTED_ENTERTAINMENT)
        {
            strr = PrimiteTypes::ToString(strr.substr(1), "optional");  
            continue; 
        }
        strr = PrimiteTypes::ToString(strr.substr(1), "must");   
    }

    std::string command = std::string(BROADCAST_COMMAND) + std::string(":") + PrimiteTypes::ToDict(broadcastDict);
    return command;
}
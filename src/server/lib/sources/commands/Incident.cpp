#include "sourceCommands.h"

std::string BTruckers::Server::Commands::Handle::Incident(BTruckers::Server::Core::DBHandler *db, std::string payload)
{
    int type;
    try{
       type  = std::stoi(PrimiteTypes::FromString(payload).value);
    }catch(...){
        return BTruckers::Server::Commands::Craft::CommandFailed("Invalid incident type");
    }   

    if(BTruckers::Shared::Enums::IncidentTypes::GetType(type)[0] == '\0')
        return BTruckers::Server::Commands::Craft::CommandFailed("Invalid incident type");

    //now we will update the incident in the database. 

    LOG_DEBUG("The payload is: %s", payload.c_str());
    LOG_DEBUG("I am the king of the world");
    return BTruckers::Server::Commands::Craft::CommandFailed("Failed to update the database");
}
#include "sourceCommands.h"

std::string BTruckers::Server::Commands::Handle::Incident(BTruckers::Server::Core::DBHandler *db, BTruckers::Server::Models::Users *user, std::string payload)
{
    std::vector<BTruckers::Shared::Structures::KeyValue> values = PrimiteTypes::FromDict(payload);
    std::string type;
    BTruckers::Shared::Structures::Cords cords;

    for(auto value : values)
    {
        if(value.key == "type")
        {
            type = value.value;
            continue;
        }
        if(value.key == "position")
        {
            cords = value.coordinates;
            continue;
        }
    }
    //this is a bit messy but it's for the best...
    std::string modifiedType = BTruckers::Shared::Enums::DataTypes::GetType(BTruckers::Shared::Enums::DataTypes::INT)+type;
    int EventType = PrimiteTypes::FromInteger(modifiedType).number;
    modifiedType = BTruckers::Shared::Enums::IncidentTypes::GetType(EventType);
    
    if(modifiedType == "")
        return BTruckers::Server::Commands::Craft::CommandFailed("Invalid incident type");

    LOG_DEBUG("The type is: %s", modifiedType.c_str());    
    
    BTruckers::Server::Models::Incidents newIncident(db);
    newIncident.UpdateField("timestamp", std::to_string(BTruckers::Shared::Utils::GetUNIXTimestamp()));
    newIncident.UpdateField("incident_type", type);
    newIncident.UpdateField("reporter_uuid", user->GetField("uuid"));
    newIncident.UpdateField("location", PrimiteTypes::ToCoordinates(cords));
    newIncident.Create();

    BTruckers::Server::Core::Broadcaster::PushMessageToQueue("'"+modifiedType+"' incident has been reported near you!");
    return BTruckers::Server::Commands::Craft::CommandSuccess("Your report of '"+ modifiedType +"' has been successfully registered.");
}
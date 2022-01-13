#include "sourceCommands.h"

std::string BTruckers::Server::Commands::Handle::ClientMetrics(BTruckers::Server::Core::DBHandler *db, BTruckers::Server::Models::Users *user, std::string payload)
{
    std::vector<BTruckers::Shared::Structures::KeyValue> data = PrimiteTypes::FromDict(payload);
    std::string speed, longitute, latitude;

    for(auto item : data)
    {
        if(item.key == "speed")
        {
            speed = item.value;
            continue;
        }

        if(item.key == "longitute")
        {
            longitute = item.value;
            continue;
        }

        if(item.key == "latitude")
        {
            latitude = item.value;
            continue;
        }
    }

    BTruckers::Server::Models::Metrics metrics(db);
    bool exists = metrics.FindBy("user_uuid", user->GetField("uuid"));
    if(!exists)
    {
        metrics.UpdateField("user_uuid", user->GetField("uuid"));
    }
    metrics.UpdateField("speed", speed);
    metrics.UpdateField("latitude", latitude);
    metrics.UpdateField("longitude", longitute);

    if(!exists)
    {
        metrics.Create();
    }else{
        metrics.Update();
    }
    int currentSpeed = std::stoi(speed);
    std::string close_time = std::to_string(BTruckers::Shared::Utils::GetUNIXTimestamp()/1000)+"%";
    BTruckers::Server::Models::Incidents incident(db);

    std::string speed_limit = std::to_string(BTruckers::Server::Utils::GetSpeedLimit(currentSpeed))+" km/h!";
    if(incident.FindBy("timestamp", close_time, "LIKE"))
    {
        if(incident.GetField("incident_type") == "21")
        {
            speed_limit = "30km/h (limited due to major accident!)";
        }else{
            speed_limit = speed_limit + " Watch out, an incident has been reported near you!";
        }
    }


    std::string response= "Successfully updated the metrics in the database. Current road speed limit is "+ speed_limit;
    return BTruckers::Server::Commands::Craft::CommandSuccess(response);
}
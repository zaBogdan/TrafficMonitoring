#include "clientCommands.h"

std::string BTruckers::Client::Commands::Craft::ReportIncident(std::string payload)
{
    std::string incident =  PrimiteTypes::ToString(payload, "type");
    BTruckers::Shared::Structures::Cords cords = BTruckers::Client::Sensors::GPS::Read();
    std::string coords = PrimiteTypes::ToCoordinates(cords, "position");
    std::vector<std::string> data {incident, coords};

    std::string command = std::string(INCIDENT_COMMAND) + std::string(":") + PrimiteTypes::ToDict(data);

    return command;
}
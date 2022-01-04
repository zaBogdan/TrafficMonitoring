#include "sourceCommands.h"
#define COMMAND_NAME "Incident"

std::string BTruckers::Client::Commands::Craft::ReportIncident(std::string payload)
{
    std::string incident =  PrimiteTypes::ToString(payload, "type");

    std::string command = std::string(INCIDENT_COMMAND) + std::string(":") + incident;

    return command;
}
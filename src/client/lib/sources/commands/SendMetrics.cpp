#include "clientCommands.h"

std::string BTruckers::Client::Commands::Craft::SendMetrics(std::string payload)
{
    LOG_DEBUG("Payload is: %s", payload.c_str());

    size_t findSpaces = payload.find(" ");

    std::string speed = payload.substr(0, findSpaces);

    size_t lastFindSpaces = findSpaces; 
    findSpaces = payload.find(" ",lastFindSpaces+1);
    std::string longitute = payload.substr(lastFindSpaces+1, findSpaces - lastFindSpaces-1);

    lastFindSpaces = findSpaces; 
    findSpaces = payload.find(" ",lastFindSpaces+1);
    std::string latitude = payload.substr(lastFindSpaces+1);

    speed = PrimiteTypes::ToString(speed, "speed");
    longitute = PrimiteTypes::ToString(longitute, "longitute");
    latitude = PrimiteTypes::ToString(latitude, "latitude");

    std::vector<std::string> finalDict {speed, longitute, latitude};
    std::string dict = PrimiteTypes::ToDict(finalDict);

    std::string command = std::string(SENDMETRICS_COMMAND) + std::string(":") + dict;

    //and that's the end.
    return command;
}
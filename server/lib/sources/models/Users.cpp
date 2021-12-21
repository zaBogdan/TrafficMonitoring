#include "models/Users.h"


//create a wrapper for DBHandler
bool BTruckers::Server::Models::Users::Execute(const char* sql)
{
    std::vector<BTruckers::Server::Structures::SQLiteResponse> response;

    if(!BTruckers::Server::Core::DBHandler::Execute(sql, response))
        return false;

    LOG_DEBUG("Response uuids 1: %s", response[0].values[0].value.c_str());
    LOG_DEBUG("Response uuids 2: %s", response[1].values[0].value.c_str());

    return true;
}

// bool BTruckers::Server::Models::Users::GetUserBy(std::string key, std::string value)
// {

// }
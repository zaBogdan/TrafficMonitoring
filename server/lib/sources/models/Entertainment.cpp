#include "models/Entertainment.h"


//constructors
BTruckers::Server::Models::Entertainment::Entertainment()
{

}



BTruckers::Server::Models::Entertainment::Entertainment(std::string identifier, std::string value)
{
    if(!this->FindBy(identifier, value))
    {
        LOG_WARNING("Failed to initialize the class. The user doesn't exists.");
        return;
    }
    this->IsInitialized() = true;
}

//functions to be overwritten
bool& BTruckers::Server::Models::Entertainment::IsLocked()
{
    return this->lockClassChanges;
}

bool& BTruckers::Server::Models::Entertainment::IsInitialized()
{
    return this->hasBeenInitialized;
}

bool& BTruckers::Server::Models::Entertainment::AllowUUIDChanges()
{
    return this->allowUUIDChanges;
}

const std::string& BTruckers::Server::Models::Entertainment::GetTableName()
{
    return this->tableName;
}

DB_FIELDS& BTruckers::Server::Models::Entertainment::GetDBFields()
{
    return this->fields;
}
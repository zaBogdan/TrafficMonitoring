#include "models/Users.h"


//constructors
BTruckers::Server::Models::Users::Users()
{

}



BTruckers::Server::Models::Users::Users(std::string identifier, std::string value)
{
    if(!this->FindBy(identifier, value))
    {
        LOG_WARNING("Failed to initialize the class. The user doesn't exists.");
        return;
    }
    this->IsInitialized() = true;
}

//functions to be overwritten
bool& BTruckers::Server::Models::Users::IsLocked()
{
    return this->lockClassChanges;
}

bool& BTruckers::Server::Models::Users::IsInitialized()
{
    return this->hasBeenInitialized;
}

bool& BTruckers::Server::Models::Users::AllowUUIDChanges()
{
    return this->allowUUIDChanges;
}

const std::string& BTruckers::Server::Models::Users::GetTableName()
{
    return this->tableName;
}

DB_FIELDS& BTruckers::Server::Models::Users::GetDBFields()
{
    return this->fields;
}
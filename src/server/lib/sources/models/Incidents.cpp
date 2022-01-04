#include "models/Incidents.h"


//constructors
BTruckers::Server::Models::Incidents::Incidents(BTruckers::Server::Core::DBHandler* db)
{
    this->dbConnection = db;
}



BTruckers::Server::Models::Incidents::Incidents(BTruckers::Server::Core::DBHandler* db, std::string identifier, std::string value)
{
    this->dbConnection = db;
    if(!this->FindBy(identifier, value))
    {
        LOG_WARNING("Failed to initialize the class. This identifier doesn't exists.");
        return;
    }
    this->IsInitialized() = true;
}

//functions to be overwritten
bool& BTruckers::Server::Models::Incidents::IsLocked()
{
    return this->lockClassChanges;
}

bool& BTruckers::Server::Models::Incidents::IsInitialized()
{
    return this->hasBeenInitialized;
}

bool& BTruckers::Server::Models::Incidents::AllowUUIDChanges()
{
    return this->allowUUIDChanges;
}

const std::string& BTruckers::Server::Models::Incidents::GetTableName()
{
    return this->tableName;
}

DB_FIELDS& BTruckers::Server::Models::Incidents::GetDBFields()
{
    return this->fields;
}

BTruckers::Server::Core::DBHandler* BTruckers::Server::Models::Incidents::GetConnection()
{
    return this->dbConnection;
}

//custom functions
#include "models/Metrics.h"


//constructors
BTruckers::Server::Models::Metrics::Metrics(BTruckers::Server::Core::DBHandler* db)
{
    this->dbConnection = db;
}

BTruckers::Server::Models::Metrics::Metrics(BTruckers::Server::Core::DBHandler* db, std::string identifier, std::string value)
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
bool& BTruckers::Server::Models::Metrics::IsLocked()
{
    return this->lockClassChanges;
}

bool& BTruckers::Server::Models::Metrics::IsInitialized()
{
    return this->hasBeenInitialized;
}

bool& BTruckers::Server::Models::Metrics::AllowUUIDChanges()
{
    return this->allowUUIDChanges;
}

const std::string& BTruckers::Server::Models::Metrics::GetTableName()
{
    return this->tableName;
}

DB_FIELDS& BTruckers::Server::Models::Metrics::GetDBFields()
{
    return this->fields;
}

BTruckers::Server::Core::DBHandler* BTruckers::Server::Models::Metrics::GetConnection()
{
    return this->dbConnection;
}

//custom functions
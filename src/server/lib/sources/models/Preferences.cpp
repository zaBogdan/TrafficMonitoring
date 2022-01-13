#include "models/Preferences.h"


//constructors
BTruckers::Server::Models::Preferences::Preferences(BTruckers::Server::Core::DBHandler* db)
{
    this->dbConnection = db;
}



BTruckers::Server::Models::Preferences::Preferences(BTruckers::Server::Core::DBHandler* db, std::string identifier, std::string value)
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
bool& BTruckers::Server::Models::Preferences::IsLocked()
{
    return this->lockClassChanges;
}

bool& BTruckers::Server::Models::Preferences::IsInitialized()
{
    return this->hasBeenInitialized;
}

bool& BTruckers::Server::Models::Preferences::AllowUUIDChanges()
{
    return this->allowUUIDChanges;
}

const std::string& BTruckers::Server::Models::Preferences::GetTableName()
{
    return this->tableName;
}

DB_FIELDS& BTruckers::Server::Models::Preferences::GetDBFields()
{
    return this->fields;
}

BTruckers::Server::Core::DBHandler* BTruckers::Server::Models::Preferences::GetConnection()
{
    return this->dbConnection;
}

//custom functions
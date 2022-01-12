#include "models/Users.h"


//constructors
BTruckers::Server::Models::Users::Users(BTruckers::Server::Core::DBHandler* db)
{
    this->dbConnection = db;
}



BTruckers::Server::Models::Users::Users(BTruckers::Server::Core::DBHandler* db, std::string identifier, std::string value)
{
    this->dbConnection = db;
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

BTruckers::Server::Core::DBHandler* BTruckers::Server::Models::Users::GetConnection()
{
    return this->dbConnection;
}



bool BTruckers::Server::Models::Users::CheckPassword(std::string plainText)
{
    LOG_DEBUG("Expected password is: %s",BTruckers::Server::Core::Tokens::SHA256(plainText).c_str());
    return (this->GetField("password") == BTruckers::Server::Core::Tokens::SHA256(plainText));
}


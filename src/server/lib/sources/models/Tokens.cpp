#include "models/Tokens.h"


//constructors
BTruckers::Server::Models::Tokens::Tokens(BTruckers::Server::Core::DBHandler* db)
{
    this->dbConnection = db;
}



BTruckers::Server::Models::Tokens::Tokens(BTruckers::Server::Core::DBHandler* db, std::string identifier, std::string value)
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
bool& BTruckers::Server::Models::Tokens::IsLocked()
{
    return this->lockClassChanges;
}

bool& BTruckers::Server::Models::Tokens::IsInitialized()
{
    return this->hasBeenInitialized;
}

bool& BTruckers::Server::Models::Tokens::AllowUUIDChanges()
{
    return this->allowUUIDChanges;
}

const std::string& BTruckers::Server::Models::Tokens::GetTableName()
{
    return this->tableName;
}

DB_FIELDS& BTruckers::Server::Models::Tokens::GetDBFields()
{
    return this->fields;
}

BTruckers::Server::Core::DBHandler* BTruckers::Server::Models::Tokens::GetConnection()
{
    return this->dbConnection;
}

bool BTruckers::Server::Models::Tokens::SetTime(int sessionDuration)
{
    std::time_t time = BTruckers::Shared::Utils::GetUNIXTimestamp();
    this->UpdateField("creation_timestamp", std::to_string(time));
    this->UpdateField("expiration_timestamp", std::to_string(time+sessionDuration));
    return true;
}

bool BTruckers::Server::Models::Tokens::VerifyToken(std::string validator)
{
    return this->GetField("validator") == BTruckers::Server::Core::Tokens::SHA256(std::string(APPLICATION_SECRET) + validator);
}



#include "models/Entertainment.h"


//constructors
BTruckers::Server::Models::Entertainment::Entertainment(BTruckers::Server::Core::DBHandler* db)
{
    this->dbConnection = db;
}



BTruckers::Server::Models::Entertainment::Entertainment(BTruckers::Server::Core::DBHandler* db,std::string identifier, std::string value)
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

BTruckers::Server::Core::DBHandler* BTruckers::Server::Models::Entertainment::GetConnection()
{
    return this->dbConnection;
}

//custom code

//to be improved...
void BTruckers::Server::Models::Entertainment::AddToBroadcasterQueue(BTruckers::Server::Core::DBHandler* db)
{
    Entertainment en(db);
    en.GetRowsCount();
    int rowsCount = std::stoi(en.GetField("rowcount"));
    std::srand(time(NULL));
    int startFrom = 1+ rand() % 3;
    while(startFrom < rowsCount)
    {
        en.FindBy("rowid", std::to_string(startFrom));
        if(en.GetField("uuid") == "")
        {
            ++startFrom;
            ++rowsCount;
        }
        
        BTruckers::Server::Core::Broadcaster::PushMessageToQueue(std::to_string(BTruckers::Server::Enums::BroadcastConditions::SELECTED_ENTERTAINMENT) + en.GetField("message"));

        startFrom += 4;
    }
}
#include "models/Users.h"

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
    this->hasBeenInitialized = true;
}

bool BTruckers::Server::Models::Users::UpdateField(std::string key, std::string value)
{
    if(this->lockClassChanges)
    {
        LOG_WARNING("This object is currently in read-only mode. Try again later");
        return false;
    }

    if(this->fields.find(key) == this->fields.end())
    {
        LOG_WARNING("The key you are trying to update is invalid.");
        return false;
    }

    //makeing it fool proof. Only internal functions can change this value.
    if(key == "uuid" && !this->allowUUIDChanges)
    {
        LOG_WARNING("You can't update the UUID of a user");
        return false;
    }

    //make sure I don't forget to set it back to false.
    this->allowUUIDChanges = false;
    
    if(key == "password")
        value = BTruckers::Server::Core::Tokens::SHA256(value);

    this->fields[key].hasChanged = true;
    this->fields[key].value = value;
    return true;
}

std::string BTruckers::Server::Models::Users::GetField(std::string key)
{
    if(this->fields.find(key) == this->fields.end())
    {
        LOG_WARNING("The key you are trying to find is invalid.");
        return "";
    }
    return this->fields[key].value;
}

//The CRUD Operations
bool BTruckers::Server::Models::Users::FindBy(std::string identifier, std::string value)
{
    std::string sql = BTruckers::Server::Core::DBHandler::PrepareSQL(
        "SELECT * FROM "+this->tableName+" WHERE "+ identifier + " = '?' LIMIT 1", 
        value.c_str());
    if(!this->Execute(sql))
    {
        LOG_WARNING("Failed to get the user.");
        return false;
    }
    this->hasBeenInitialized = true;
    return true;
}

bool BTruckers::Server::Models::Users::Create()
{
    if(this->GetField("uuid") != "")
    {
        LOG_WARNING("This user already exists.");
        return false;
    }

    this->allowUUIDChanges = true;
    this->UpdateField("uuid", BTruckers::Server::Core::Tokens::UUID());
    this->allowUUIDChanges = false;

    std::string keys = "(", values = "(";
    for(auto field : this->fields)
    {
        if(field.second.hasChanged)
        {
            keys += field.first + ",";
            values += BTruckers::Server::Core::DBHandler::PrepareSQL(
                "'?',",
                field.second.value.c_str()
            );
        }
    }
    keys[keys.size()-1] = ')';
    values[values.size()-1] = ')';
    std::string sql = "INSERT INTO " + this->tableName + keys + " VALUES " + values +";";

    this->lockClassChanges = true;
    if(!this->Execute(sql))
    {
        LOG_WARNING("Failed to create the user.");
        return false;
    }

    this->hasBeenInitialized = true;
    return true;
}

bool BTruckers::Server::Models::Users::Update()
{
    if(!this->hasBeenInitialized)
        return false;

    std::string uuid = this->GetField("uuid");
    if(uuid == "")
        return false;

    bool atLeastOnefield = false;
    
    std::string sql = "UPDATE "+this->tableName+" SET ";
    for(auto field : this->fields)
    {
        if(field.second.hasChanged)
        {
            atLeastOnefield = true;
            sql += field.first + "=";
            sql += BTruckers::Server::Core::DBHandler::PrepareSQL(
                "'?', ",
                field.second.value.c_str()
            );
        }
    }
    if(!atLeastOnefield)
        return false;
    sql.erase(sql.length()-2,1);

    sql += "WHERE uuid = '?';";
    sql = BTruckers::Server::Core::DBHandler::PrepareSQL(sql, uuid.c_str());
    
    if(!this->Execute(sql))
    {
        LOG_WARNING("Failed to update the user.");
        return false;
    }

    return false;
}

bool BTruckers::Server::Models::Users::Delete()
{
    if(!this->hasBeenInitialized)
        return false;

    std::string uuid = this->GetField("uuid");
    if(uuid == "")
        return false;
    
    std::string sql = BTruckers::Server::Core::DBHandler::PrepareSQL(
        "DELETE FROM " + this->tableName + " WHERE uuid='?'",
        uuid.c_str()
    );
    this->lockClassChanges = true;
    if(!this->Execute(sql))
    {
        LOG_WARNING("Failed to delete the user.");
        return false;
    }
    
    return false;
}

//some helpers
bool BTruckers::Server::Models::Users::Execute(std::string sql)
{
    std::vector<BTruckers::Server::Structures::SQLiteResponse> response;

    if(!BTruckers::Server::Core::DBHandler::Execute(sql.c_str(), response))
        return false;

    //if we don't need to populate the class we will lea ve it like this.
    if(this->lockClassChanges)
        return true;

    if(!response.size())
        return false;

    BTruckers::Server::Models::Users::Populate(*this, response[0]);
    this->hasBeenInitialized = true;

    return true;
}

bool BTruckers::Server::Models::Users::Populate(BTruckers::Server::Models::Users& current, BTruckers::Server::Structures::SQLiteResponse& data)
{
    for(int idx=0;idx<data.count;++idx)
    {
        current.fields[data.values[idx].key].value = data.values[idx].value;
        current.fields[data.values[idx].key].hasChanged = false; 
    }

    return true;
}

void BTruckers::Server::Models::Users::Print()
{
    LOG_DEBUG("-=-=-=-=-= User Model -=-=-=-=-=");
    for(auto field : this->fields)
    {
        LOG_DEBUG("%s : %s (%s)", 
            field.first.c_str(), 
            (field.second.value == "" ? "(null)" : field.second.value.c_str()),
            (field.second.hasChanged ? "modified" : "same")
            );

    }
    LOG_DEBUG("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
}

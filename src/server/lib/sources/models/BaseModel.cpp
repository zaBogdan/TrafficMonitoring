#include "models/BaseModel.h"

bool BTruckers::Server::Models::BaseModel::UpdateField(std::string key, std::string value)
{
    if(this->IsLocked())
    {
        LOG_WARNING("This object is currently in read-only mode. Try again later");
        return false;
    }

    if(this->GetDBFields().find(key) == this->GetDBFields().end())
    {
        LOG_WARNING("The key you are trying to update is invalid.");
        return false;
    }

    //makeing it fool proof. Only internal functions can change this value.
    if(key == "uuid" && !this->AllowUUIDChanges())
    {
        LOG_WARNING("You can't update the UUID of a user");
        return false;
    }

    //make sure I don't forget to set it back to false.
    this->AllowUUIDChanges() = false;
    
    if(key == "password")
        value = BTruckers::Server::Core::Tokens::SHA256(value);

    this->GetDBFields()[key].hasChanged = true;
    this->GetDBFields()[key].value = value;
    return true;
}

std::string BTruckers::Server::Models::BaseModel::GetField(std::string key)
{
    DB_FIELDS fields = this->GetDBFields();

    if(fields.find(key) == fields.end())
    {
        LOG_WARNING("The key you are trying to find is invalid.");
        return "";
    }
    return fields[key].value;
}

//The CRUD Operations
bool BTruckers::Server::Models::BaseModel::FindBy(std::string identifier, std::string value, std::string customWhere)
{
    std::string sql = BTruckers::Server::Core::DBHandler::PrepareSQL(
        "SELECT * FROM "+this->GetTableName()+" WHERE "+ identifier + " " + customWhere +" '?' LIMIT 1", 
        value.c_str());
    if(!this->Execute(sql))
    {
        LOG_WARNING("Failed to get the user.");
        return false;
    }
    // this->IsInitialized() = true;
    return true;
}

bool BTruckers::Server::Models::BaseModel::Create()
{
    if(this->GetField("uuid") != "")
    {
        LOG_WARNING("This user already exists.");
        return false;
    }

    this->AllowUUIDChanges() = true;
    this->UpdateField("uuid", BTruckers::Server::Core::Tokens::UUID());
    this->AllowUUIDChanges() = false;

    std::string keys = "(", values = "(";
    for(auto field : this->GetDBFields())
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
    std::string sql = "INSERT INTO " + this->GetTableName() + keys + " VALUES " + values +";";

    this->IsLocked() = true;
    if(!this->Execute(sql))
    {
        LOG_WARNING("Failed to create the user.");
        return false;
    }

    this->IsInitialized() = true;
    return true;
}

bool BTruckers::Server::Models::BaseModel::Update()
{
    if(!this->IsInitialized())
        return false;

    std::string uuid = this->GetField("uuid");
    if(uuid == "")
        return false;

    bool atLeastOnefield = false;
    
    std::string sql = "UPDATE "+this->GetTableName()+" SET ";
    for(auto field : this->GetDBFields())
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

bool BTruckers::Server::Models::BaseModel::Delete()
{
    if(!this->IsInitialized())
        return false;

    std::string uuid = this->GetField("uuid");
    
    if(uuid == "")
        return false;
    
    std::string sql = BTruckers::Server::Core::DBHandler::PrepareSQL(
        "DELETE FROM " + this->GetTableName() + " WHERE uuid='?'",
        uuid.c_str()
    );
    
    this->IsLocked() = true;

    if(!this->Execute(sql))
    {
        LOG_WARNING("Failed to delete the user.");
        return false;
    }
    
    return false;
}

//get rows
bool BTruckers::Server::Models::BaseModel::GetRowsCount()
{
    return this->Execute("select count(*) as rowcount from "+this->GetTableName());
}

//some helpers
bool BTruckers::Server::Models::BaseModel::Execute(std::string sql)
{
    std::vector<BTruckers::Server::Structures::SQLiteResponse> response;

    if(!this->GetConnection()->Execute(sql.c_str(), response))
        return false;

    //if we don't need to populate the class we will lea ve it like this.
    if(this->IsLocked())
        return true;

    if(!response.size())
        return false;
    
    BTruckers::Server::Models::BaseModel::Populate(*this, response[0]);

    this->IsInitialized() = true;

    return true;
}

bool BTruckers::Server::Models::BaseModel::Populate(BTruckers::Server::Models::BaseModel& current, BTruckers::Server::Structures::SQLiteResponse& data)
{
    for(int idx=0;idx<data.count;++idx)
    {
        current.GetDBFields()[data.values[idx].key].value = data.values[idx].value;
        current.GetDBFields()[data.values[idx].key].hasChanged = false; 
    }

    return true;
}

void BTruckers::Server::Models::BaseModel::Print()
{
    LOG_DEBUG("-=-=-=-=-= Base Model -=-=-=-=-=");
    for(auto field : this->GetDBFields())
    {
        LOG_DEBUG("%s : %s (%s)", 
            field.first.c_str(), 
            (field.second.value == "" ? "(null)" : field.second.value.c_str()),
            (field.second.hasChanged ? "modified" : "same")
            );

    }
    LOG_DEBUG("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
}

#include "models/Users.h"



//create a wrapper for DBHandler
bool BTruckers::Server::Models::Users::GetUserBy(std::string key, std::string value)
{
    std::vector<BTruckers::Server::Structures::SQLiteResponse> response;
    std::string sql = BTruckers::Server::Core::DBHandler::PrepareSQL("SELECT * FROM "+this->tabelName+" WHERE ?='?' LIMIT 1;", key.c_str(), value.c_str());
    LOG_DEBUG("SQL to be executed is: %s", sql.c_str());
    
    if(!BTruckers::Server::Core::DBHandler::Execute(sql.c_str(), response))
        return false;

    if(!response.size())
        return false;
    
    BTruckers::Server::Models::Users::PopulateClass(*this, response[0]);
    //this will work only on debug context
    this->Print();
    return true;
}

bool BTruckers::Server::Models::Users::PopulateClass(BTruckers::Server::Models::Users& current, BTruckers::Server::Structures::SQLiteResponse& data)
{
    for(int idx=0;idx<data.count;++idx)
    {
        do{
            CHECK_BREAK(data.values[idx].key == "username", current.username = data.values[idx].value);
            CHECK_BREAK(data.values[idx].key == "uuid", current.uuid = data.values[idx].value);
            CHECK_BREAK(data.values[idx].key == "password", current.password = data.values[idx].value);
            CHECK_BREAK(data.values[idx].key == "firstname", current.firstname = data.values[idx].value);
            CHECK_BREAK(data.values[idx].key == "lastname", current.lastname = data.values[idx].value);
            CHECK_BREAK(data.values[idx].key == "email", current.email = data.values[idx].value);
            CHECK_BREAK(data.values[idx].key == "company", current.company = data.values[idx].value);          
            //assure that we don't stall
            LOG_WARNING("FAILED TO assign the key '%s' to the value '%s'",data.values[idx].key.c_str(), data.values[idx].value.c_str())
            break;
        }while(true);
    }
    return true;
}


std::string BTruckers::Server::Models::Users::SQLStatemFromVariables(std::string syntax)
{
    std::string sqlStatement = "";
    sqlStatement = BTruckers::Server::Utils::FormatFromString(syntax, "_","uuid", this->uuid.c_str());
    BTruckers::Server::Utils::AddNewChar(sqlStatement, ",)", "_,");  
    sqlStatement = BTruckers::Server::Utils::FormatFromString(sqlStatement, "_","username", this->username.c_str());
    BTruckers::Server::Utils::AddNewChar(sqlStatement, ",)", "_,");
    sqlStatement = BTruckers::Server::Utils::FormatFromString(sqlStatement, "_","email", this->email.c_str());
    BTruckers::Server::Utils::AddNewChar(sqlStatement, ",)", "_,");
    sqlStatement = BTruckers::Server::Utils::FormatFromString(sqlStatement, "_","password", this->password.c_str());
    BTruckers::Server::Utils::AddNewChar(sqlStatement, ",)", "_,");
    sqlStatement = BTruckers::Server::Utils::FormatFromString(sqlStatement, "_","firstname", this->firstname.c_str());
    BTruckers::Server::Utils::AddNewChar(sqlStatement, ",)", "_,");
    sqlStatement = BTruckers::Server::Utils::FormatFromString(sqlStatement, "_","lastname", this->lastname.c_str());
    BTruckers::Server::Utils::AddNewChar(sqlStatement, ",)", "_,");
    sqlStatement = BTruckers::Server::Utils::FormatFromString(sqlStatement, "_","company", this->company.c_str());
    // sqlStatement += 
    // "_ = _"
    // "(_) VALUES (_)"
    // SET column1 = value1, column2 = value2, ...

    // (column1, column2, column3, ...)
    // VALUES (value1, value2, value3, ...);
    // return BTruckers::Server::Core::DBHandler::PrepareSQL(
    //     statement,
    // ); 
    return sqlStatement;
}


void BTruckers::Server::Models::Users::Print()
{
    LOG_DEBUG("-=-=-=-=-= User Model -=-=-=-=-=");
    LOG_DEBUG("UUID: %s", this->uuid.c_str());
    LOG_DEBUG("Username: %s", this->username.c_str());
    LOG_DEBUG("Email: %s", this->email.c_str());
    LOG_DEBUG("Password: %s", this->password.c_str());
    LOG_DEBUG("Firstname: %s", this->firstname.c_str());
    LOG_DEBUG("Lastname: %s", this->lastname.c_str());
    LOG_DEBUG("Company: %s", this->company.c_str());
    LOG_DEBUG("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
}

bool BTruckers::Server::Models::Users::Create()
{
    if(this->GetUserByUUID())
    {
        LOG_WARNING("The user with uuid '%s' already exists.");
        return false;
    }
    this->SQLStatemFromVariables("(_,) VALUES (_,)");
    return false;
}
bool BTruckers::Server::Models::Users::Update()
{
    return false;
}

bool BTruckers::Server::Models::Users::Delete()
{
    //if the user isn't yet populated with the UUID we can't run this method.
    if(this->uuid == "")
        return false;

    std::string sql = BTruckers::Server::Core::DBHandler::PrepareSQL("DELETE FROM "+this->tabelName+" WHERE uuid='?';", this->uuid.c_str());
    if(!BTruckers::Server::Core::DBHandler::Execute(sql.c_str()))
        return false;
    
    return true;
}


//per model functions
bool BTruckers::Server::Models::Users::GetUserByUUID(std::string value)
{
    if(value == "")
        value = this->uuid;
    return this->GetUserBy("uuid", value);
}
bool BTruckers::Server::Models::Users::GetUserByUsername(std::string value)
{
    if(value == "")
        value = this->username;
    return this->GetUserBy("username", value);
}
bool BTruckers::Server::Models::Users::GetUserByEmail(std::string value)
{
    if(value == "")
        value = this->email;
    return this->GetUserBy("email", value);
}
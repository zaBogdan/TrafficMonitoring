#include "models/Users.h"

//create a wrapper for DBHandler
bool BTruckers::Server::Models::Users::Execute(std::string sql, bool populate)
{
    if(!BTruckers::Server::Core::DBHandler::Execute(sql.c_str(), response))
        return false;

    //if we don't need to populate the class we will lea ve it like this.
    if(!populate || this->PopulateClassDisabled)
        return true;

    if(!response.size())
        return false;

    BTruckers::Server::Models::Users::PopulateClass(*this, response[0]);

    //this will work only on debug context
    this->Print();

    return true;
}

bool BTruckers::Server::Models::Users::GetUserBy(std::string key, std::string value)
{
    std::string sql = BTruckers::Server::Core::DBHandler::PrepareSQL("SELECT * FROM "+this->tabelName+" WHERE ?='?' LIMIT 1;", key.c_str(), value.c_str());
    
    return this->Execute(sql);
}

bool BTruckers::Server::Models::Users::Create()
{
    if(this->GetUserByUUID() || this->GetUserByUsername() || this->GetUserByEmail())
    {
        LOG_WARNING("The user with same uuid/username/email '%s' already exists.", this->uuid.c_str());
        return false;
    }
    this->uuid = BTruckers::Server::Core::Tokens::UUID();
    if(this->password == "")
        return false;
        
    this->password = BTruckers::Server::Core::Tokens::SHA256(this->password);
    std::string sql = BTruckers::Server::Core::DBHandler::PrepareSQL(
        "INSERT INTO "+this->tabelName+" (uuid, username, email, password, firstname, lastname, company)"+
        " VALUES ('?','?','?','?','?','?','?');",
        this->uuid.c_str(),
        this->username.c_str(),
        this->email.c_str(),
        this->password.c_str(),
        this->firstname.c_str(),
        this->lastname.c_str(),
        this->company.c_str()
        );
    
    return this->Execute(sql);
}

bool BTruckers::Server::Models::Users::Update()
{
    this->PopulateClassDisabled = true;
    if(!this->GetUserByUUID() && !this->GetUserByUsername() && !this->GetUserByEmail())
    {
        LOG_WARNING("The user with uuid '%s' doesn't exists.", this->uuid.c_str());
        return false;
    }
    
    this->password = BTruckers::Server::Core::Tokens::SHA256(this->password);

    LOG_DEBUG("Starting to execute the sql;");
    std::string sql = BTruckers::Server::Core::DBHandler::PrepareSQL(
        "UPDATE "+this->tabelName+" SET "+
        "username = '?', "+
        "email = '?', "+
        "password = '?', "+
        "firstname = '?', "+
        "lastname = '?', "+
        "company = '?' where uuid = '?';",
        this->username.c_str(),
        this->email.c_str(),
        this->password.c_str(),
        this->firstname.c_str(),
        this->lastname.c_str(),
        this->company.c_str(),
        this->uuid.c_str()
        );
    
    LOG_DEBUG("SQL is: %s", sql.c_str());
    if(!this->Execute(sql))
    {
        LOG_WARNING("The UPDATE sql failed to run.");
        this->PopulateClassDisabled = false;
        return false;
    }
    LOG_WARNING("The sql is successfull");
    this->PopulateClassDisabled = false;

    return true;
}

bool BTruckers::Server::Models::Users::Delete()
{
    //if the user isn't yet populated with the UUID we can't run this method.
    if(this->uuid == "")
        return false;

    std::string sql = BTruckers::Server::Core::DBHandler::PrepareSQL("DELETE FROM "+this->tabelName+" WHERE uuid='?';", this->uuid.c_str());
    
    //we don't need to populate this
    return this->Execute(sql.c_str(),false);
}

std::string BTruckers::Server::Models::Users::GetUserUUID()
{
    return this->uuid;
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
#include "DBHandler.h"

sqlite3* BTruckers::Server::Core::DBHandler::connection = nullptr;

int BTruckers::Server::Core::DBHandler::CallbackFunction(void *instance, int argc, char **argv, char **azColName)
{
    std::vector<BTruckers::Server::Structures::SQLiteResponse> *tmpVector = (std::vector<BTruckers::Server::Structures::SQLiteResponse>*) instance;
    BTruckers::Server::Structures::SQLiteResponse tmp;
    BTruckers::Shared::Structures::KeyValue pair;
    tmp.count = argc;

    for(int i = 0; i<tmp.count; ++i) {
        pair.key = azColName[i];
        pair.value = argv[i] ? argv[i] : "NULL";
        tmp.values.push_back(pair);
    }
    tmpVector->push_back(tmp);

    return 0;
}

bool BTruckers::Server::Core::DBHandler::Execute(const char* sql, std::vector<BTruckers::Server::Structures::SQLiteResponse>& response)
{
    //checking if we have an active connection to the database
    if(BTruckers::Server::Core::DBHandler::connection == nullptr)
    {
        LOG_ERROR("You first need to establish a connection to the database");
        return false;
    }
    
    char *zErrMsg = 0;
    int rc = sqlite3_exec(BTruckers::Server::Core::DBHandler::connection, sql, BTruckers::Server::Core::DBHandler::CallbackFunction, &response, &zErrMsg);
    LOG_DEBUG("RC is: %d", rc);
    if(!rc)
        return true;
    LOG_WARNING("Failed to run the query '%s' with the following error: '%s'", sql, zErrMsg);
    return false;
}

/**
 * @brief Constructor and destructor with their aid functions 
 */
//Contructor
BTruckers::Server::Core::DBHandler::DBHandler()
{
    if(BTruckers::Server::Core::DBHandler::connection == nullptr)
    {
        if(!this->InitiateConnection())
        {
            exit(12);
        }
        LOG_INFO("Connection to the database '%s' established successfully.", DATABASE_FILENAME);
    }else{
        LOG_WARNING("You can't initiate two connections of DBHandler!");
    }
}

//Aid for constructor
bool BTruckers::Server::Core::DBHandler::InitiateConnection()
{
    if(BTruckers::Server::Core::DBHandler::connection != nullptr)
        return true;

    char *zErrMsg = 0;
    int rc;
    rc = sqlite3_open(DATABASE_FILENAME, &BTruckers::Server::Core::DBHandler::connection);
    if(rc) {
        LOG_ERROR("Failed to open '%s'. Exiting the app...", sqlite3_errmsg(BTruckers::Server::Core::DBHandler::connection));
        return false;
    } 
    return true;
}

//destructor
BTruckers::Server::Core::DBHandler::~DBHandler()
{
    LOG_DEBUG("Closing the database connection");
    sqlite3_close(BTruckers::Server::Core::DBHandler::connection);    
}
#include "DBHandler.h"

sqlite3* BTruckers::Server::Core::DBHandler::connection = nullptr;

BTruckers::Server::Core::DBHandler::DBHandler()
{
    if(BTruckers::Server::Core::DBHandler::connection == nullptr)
    {
        if(!this->InitiateConnection())
        {
            exit(12);
        }
        LOG_INFO("Connection to the database '%s' established successfully.", DATABASE_FILENAME);
    }
}

bool BTruckers::Server::Core::DBHandler::InitiateConnection()
{
    char *zErrMsg = 0;
    int rc;
    rc = sqlite3_open(DATABASE_FILENAME, &BTruckers::Server::Core::DBHandler::connection);
    if(rc) {
        LOG_ERROR("Failed to open '%s'. Exiting the app...", sqlite3_errmsg(BTruckers::Server::Core::DBHandler::connection));
        return false;
    } 
    return true;
}

BTruckers::Server::Core::DBHandler::~DBHandler()
{
    LOG_DEBUG("Closing the database connection");
    sqlite3_close(BTruckers::Server::Core::DBHandler::connection);    
}

int BTruckers::Server::Core::DBHandler::CallbackFunction(void *NotUsed, int argc, char **argv, char **azColName)
{
    //just to avoid the not used warning.
    NotUsed = nullptr;
    int i;
    LOG_DEBUG("[ Database ] Using the default callback function...");
    LOG_DEBUG("=========DBObject=========");
    for(i = 0; i<argc; i++) {
        LOG_DEBUG("%s = %s", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    LOG_DEBUG("==========================");
    return 0;
}

bool BTruckers::Server::Core::DBHandler::Execute(const char* sql)
{
    char *zErrMsg = 0;
    int rc = sqlite3_exec(BTruckers::Server::Core::DBHandler::connection, sql, BTruckers::Server::Core::DBHandler::CallbackFunction, 0, &zErrMsg);
    return false;
}
#include "DBHandler.h"

std::vector<BTruckers::Server::Structures::SQLiteResponse> BTruckers::Server::Core::DBHandler::nothingToRespondTo = {};

int BTruckers::Server::Core::DBHandler::CallbackFunction(void *instance, int argc, char **argv, char **azColName)
{
    std::vector<BTruckers::Server::Structures::SQLiteResponse> *tmpVector = (std::vector<BTruckers::Server::Structures::SQLiteResponse>*) instance;
    if(tmpVector == &BTruckers::Server::Core::DBHandler::nothingToRespondTo)
    {
        LOG_DEBUG("Nothing to do here. No need for response");
        return 0;
    }
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
    if(this->connection == nullptr)
    {
        LOG_ERROR("You first need to establish a connection to the database");
        return false;
    }

    char *zErrMsg = 0;
    // sqlite3_mutex_enter(sqlite3_db_mutex(BTruckers::Server::Core::DBHandler::connection));
    // LOG_DEBUG("Entering now...");
    int rc = sqlite3_exec(this->connection, sql, BTruckers::Server::Core::DBHandler::CallbackFunction, &response, nullptr);
    // sqlite3_mutex_leave(sqlite3_db_mutex(BTruckers::Server::Core::DBHandler::connection));

    if(!rc)
        return true;

    LOG_WARNING("Failed to run the query '%s' with the following error: '%s'", sql, zErrMsg);
    return false;
}

std::string BTruckers::Server::Core::DBHandler::PrepareSQL(std::string sql,...)
{
    //get the number of arguments (I will always override this one)
    size_t count = std::count(sql.begin(), sql.end(), '?');

    //for each argument we will replace the '?'
    va_list args;
    va_start(args, sql);
    for(size_t idx=0;idx<count;++idx)
    {
        size_t pos = sql.find("?");
        std::string substituter = va_arg(args, char*);

        //doing some sanitization (not the best it should do the trick)
        substituter.erase(std::remove(substituter.begin(), substituter.end(), '\''), substituter.end());
        substituter.erase(std::remove(substituter.begin(), substituter.end(), ';'), substituter.end());
        substituter.erase(std::remove(substituter.begin(), substituter.end(), '\"'), substituter.end());

        if(pos == std::string::npos)
        {
            LOG_WARNING("Failed to find the place where to substitute '%s'. Exiting...", substituter.c_str());
            break;
        }
        //erase the ?
        sql.erase(pos,1);
        //insert the value
        sql.insert(pos,substituter);
    }
    va_end(args);
    return sql;
}


/**
 * @brief Constructor and destructor with their aid functions 
 */
//Contructor
BTruckers::Server::Core::DBHandler::DBHandler()
{
    if(this->connection == nullptr)
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
    if(this->connection != nullptr)
        return true;

    char *zErrMsg = 0;
    int rc;
    // sqlite3_config(SQLITE_CONFIG_MULTITHREAD,SQLITE_OPEN_FULLMUTEX);
    rc = sqlite3_open(DATABASE_FILENAME, &this->connection);
    if(rc) {
        LOG_ERROR("Failed to open '%s'. Exiting the app...", sqlite3_errmsg(this->connection));
        return false;
    } 
    return true;
}

//destructor
BTruckers::Server::Core::DBHandler::~DBHandler()
{
    LOG_INFO("Closing the connection to database");
    sqlite3_close(this->connection);    
}
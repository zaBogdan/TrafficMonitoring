#include "DBHandler.h"

sqlite3* BTruckers::Server::Core::DBHandler::connection = nullptr;

/**
 * @brief The function that executes all the queries.
 * 
 * @param sql the sql statemnt to be executed
 * @return true when the query was successfull and the callback function was called
 * @return false otherwise
 */
bool BTruckers::Server::Core::DBHandler::Execute(const char* sql)
{
    char response[200];
    char *zErrMsg = 0;
    int rc = sqlite3_exec(BTruckers::Server::Core::DBHandler::connection, sql, BTruckers::Server::Core::DBHandler::CallbackFunction, &response, &zErrMsg);
    LOG_DEBUG("Finished executing with: %d", rc);
    LOG_DEBUG("Response is: %s", response);
    if(!rc)
        return true;
    LOG_WARNING("Failed to run the query '%s'. Check out if it's correct.", sql);
    return false;
}

/**
 * @brief The default callback function for each query. It's just for printing
 * 
 * @param NotUsed 
 * @param argc 
 * @param argv 
 * @param azColName 
 * @return the status 0 if successfull.
 */
int BTruckers::Server::Core::DBHandler::CallbackFunction(void *instance, int argc, char **argv, char **azColName)
{
    //just to avoid the not used warning.
    // = "hello zabogdan from data.";
    // char* response = (char*) instance;
    // response = zabogdan;
    // char zabogdan[200] = "hello zabogdan from data";
    // instance = zabogdan;
    //i need to create a new structure that will be using 3 types: argc, argv, azColName. From this I will just assign them.
    char *tmp = (char*) instance;
    tmp[0] = 'z';
    tmp[1] = 'a';
    tmp[2] = 'b';
    tmp[3] = 'o';
    tmp[4] = 'g';
    tmp[5] = 'd';
    tmp[6] = 'a';
    tmp[7] = 'n';
    tmp[8] = 0;
    // LOG_DEBUG("Data is: %s", zabogdan);
    // LOG_DEBUG("Data is: %s", instance);
    // LOG_DEBUG("The name of class is: %s", typeid(instance).name());
    // if(dynamic_cast<BTruckers::Server::Models::Users*>(instance))
    // {
    //     LOG_DEBUG("Is an user model.");
    // }
    // auto x = static_cast<typeid(A).name()>(instance);
    // x->CallbackFunction(argc, argv, azColName);
    // return 0;
    // int i;
    // LOG_DEBUG("[ Database ] Using the default callback function...");
    // LOG_DEBUG("=========DBObject=========");
    // for(i = 0; i<argc; i++) {
    //     LOG_DEBUG("%s = %s", azColName[i], argv[i] ? argv[i] : "NULL");
    // }
    // LOG_DEBUG("==========================");
    return 0;
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
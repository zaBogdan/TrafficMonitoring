#include "models/Users.h"


int BTruckers::Server::Models::Users::CallbackFunction(void* notUsed, int argc, char **argv, char **azColName)
{
    LOG_WARNING("Hello world from my callback function");
    return 0;
}

//create a wrapper for DBHandler
bool BTruckers::Server::Models::Users::Execute(const char* sql)
{
//    return BTruckers::Server::Core::DBHandler::Execute(sql, this->CallbackFunction);
}
// BTruckers::Server::Models::Users GetUserByID(const char* id)
// {
//     BTruckers::Server::Models::Users user;
//     this->Execute("select * from users where username = 'zabogdan'");
//     return user;
// }

#pragma once
#include "BTRCommon.h"
#include "Tokens.h"
#include <sqlite3.h> 
#include <cstdarg>

namespace BTruckers
{
    namespace Server
    {
        namespace Core
        {
               class DBHandler
               {
                    protected:
                        sqlite3 *connection;
                        static std::vector<BTruckers::Server::Structures::SQLiteResponse> nothingToRespondTo;

                    private: 
                        static int CallbackFunction(void *instance, int argc, char **argv, char **azColName);
                        bool InitiateConnection();
                    public:
                        DBHandler();
                        ~DBHandler();
                        static std::string PrepareSQL(std::string sql,...);
                        bool Execute(const char* sql, std::vector<BTruckers::Server::Structures::SQLiteResponse>& response = BTruckers::Server::Core::DBHandler::nothingToRespondTo);
               };
        }  
    }     
}
//Some of the code comes from https://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm
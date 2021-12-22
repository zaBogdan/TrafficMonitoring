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
                        static sqlite3 *connection;
                        static std::vector<BTruckers::Server::Structures::SQLiteResponse> nothingToRespondTo;

                    private: 
                        static int CallbackFunction(void *instance, int argc, char **argv, char **azColName);
                        bool InitiateConnection();
                    public:
                        DBHandler();
                        ~DBHandler();
                        static std::string PrepareSQL(std::string sql,...);
                        static bool Execute(const char* sql, std::vector<BTruckers::Server::Structures::SQLiteResponse>& response = BTruckers::Server::Core::DBHandler::nothingToRespondTo);
                        static bool AddIfNotNULL(std::string& sql,const char* key, std::string variable, std::string syntax);
               };
        }  
    }     
}
//Some of the code comes from https://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm
#pragma once
#include "BTRCommon.h"
#include <sqlite3.h> 

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

                    private: 
                        static int CallbackFunction(void *instance, int argc, char **argv, char **azColName);
                        bool InitiateConnection();
                    public:
                        DBHandler();
                        ~DBHandler();
                        static bool Execute(const char* sql);
               };
        }  
    }     
}
//Some of the code comes from https://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm
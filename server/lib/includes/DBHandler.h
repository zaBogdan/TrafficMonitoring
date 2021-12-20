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
                        static int CallbackFunction(void *NotUsed, int argc, char **argv, char **azColName);
                        bool InitiateConnection();
                    public:
                        DBHandler();
                        ~DBHandler();
                        bool Execute(const char* sql);

               };
        }  
    }     
}

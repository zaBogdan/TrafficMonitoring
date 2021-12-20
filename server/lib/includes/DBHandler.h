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
                    std::string tableName;
                    
                    public:
                        DBHandler();

               };
        }  
    }     
}

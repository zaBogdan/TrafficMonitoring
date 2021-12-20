#pragma once
#include "BTRCommon.h"
#include "DBHandler.h"

namespace BTruckers
{
    namespace Server
    {
        namespace Models
        {
            class Users
            {
                private:
                    int CallbackFunction(void* notUsed, int argc, char **argv, char **azColName);
                    const char* tabelName = "users";

                    std::string uuid;
                    std::string username;
                    std::string password;
                public:
                    Users() = default;
                    bool Execute(const char* sql);
            };
        }
    }
}
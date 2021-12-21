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
                public: 
                    std::string uuid = "";
                    std::string username = "";
                    std::string password = "";
                    std::string email = "";
                    std::string firstname = "";
                    std::string lastname = "";
                    std::string company = "";
                private:
                    const char* tabelName = "users";
                    static bool PopulateClass(BTruckers::Server::Models::Users& current, BTruckers::Server::Structures::SQLiteResponse& data);
                public:
                    Users() = default;
                    bool Execute(const char* sql);
                    void Print();

                    bool GetUserBy(std::string key, std::string value);
            };
        }
    }
}
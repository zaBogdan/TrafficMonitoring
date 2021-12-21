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
                    const std::string tabelName = "users";
                    static bool PopulateClass(BTruckers::Server::Models::Users& current, BTruckers::Server::Structures::SQLiteResponse& data);
                public:
                    Users() = default;
                    void Print();

                    //the Read Functions
                    bool GetUserBy(std::string key, std::string value);
                    bool GetUserByUUID(std::string value);
                    bool GetUserByUsername(std::string value);
                    bool GetUserByEmail(std::string value);
                    
                    //the CUD functions
                    bool Create();
                    bool Update();
                    bool Delete();
            };
        }
    }
}
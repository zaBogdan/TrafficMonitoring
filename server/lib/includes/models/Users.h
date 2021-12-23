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
                    std::string username = "";
                    std::string password = "";
                    std::string email = "";
                    std::string firstname = "";
                    std::string lastname = "";
                    std::string company = "";
                private:
                    std::string uuid = "";
                    bool PopulateClassDisabled = false;
                    const std::string tabelName = "users";
                    std::vector<BTruckers::Server::Structures::SQLiteResponse> response;

                    static bool PopulateClass(BTruckers::Server::Models::Users& current, BTruckers::Server::Structures::SQLiteResponse& data);
                    bool Execute(std::string sql,bool populate = true);
                public:
                    Users() = default;
                    void Print();

                    std::string GetUserUUID();
                    
                    //the Read Functions
                    bool GetUserBy(std::string key, std::string value);
                    bool GetUserByUUID(std::string value = "");
                    bool GetUserByUsername(std::string value = "");
                    bool GetUserByEmail(std::string value = "");
                    
                    //the CUD functions
                    bool Create();
                    bool Update();
                    bool Delete();
            };
        }
    }
}
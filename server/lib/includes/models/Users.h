#pragma once
#include "BTRCommon.h"
#include "DBHandler.h"
#include <unordered_map>

namespace BTruckers
{
    namespace Server
    {
        namespace Models
        {
            class Users
            {
                private:
                    const std::string tableName = "users";
                    DB_FIELDS fields = {
                        {"uuid", BTruckers::Shared::Structures::TrackChanges{}},
                        {"username", BTruckers::Shared::Structures::TrackChanges{}},
                        {"email", BTruckers::Shared::Structures::TrackChanges{}},
                        {"password", BTruckers::Shared::Structures::TrackChanges{}},
                        {"firstname", BTruckers::Shared::Structures::TrackChanges{}},
                        {"lastname", BTruckers::Shared::Structures::TrackChanges{}},
                        {"company", BTruckers::Shared::Structures::TrackChanges{}},
                    };
                    
                    bool lockClassChanges = false;
                    bool hasBeenInitialized = false;
                    bool allowUUIDChanges = false;
                    static bool Populate(BTruckers::Server::Models::Users& current, BTruckers::Server::Structures::SQLiteResponse& data);
                    bool Execute(std::string sql);

                public:
                    Users();
                    Users(std::string identifier, std::string value);

                    //CRUD
                    bool FindBy(std::string identifier, std::string value);
                    bool Create();
                    bool Update();
                    bool Delete();

                    //Update field
                    bool UpdateField(std::string key, std::string value);
                    std::string GetField(std::string key);

                    //print the variables
                    void Print();

            };
        }
    }
}

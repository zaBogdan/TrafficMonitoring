#pragma once
#include "BTRCommon.h"
#include "DBHandler.h"
#include "models/BaseModel.h"
#include "Broadcaster.h"
#include <unordered_map>

namespace BTruckers
{
    namespace Server
    {
        namespace Models
        {
            class Preferences : public BaseModel
            {
                private:
                    const std::string tableName = "users_preferences";
                    DB_FIELDS fields = {
                        {"uuid", BTruckers::Shared::Structures::TrackChanges{}},
                        {"user_uuid", BTruckers::Shared::Structures::TrackChanges{}},
                        {"media", BTruckers::Shared::Structures::TrackChanges{}},
                        {"save_storage", BTruckers::Shared::Structures::TrackChanges{}},
                    };
                
                    bool lockClassChanges = false;
                    bool hasBeenInitialized = false;
                    bool allowUUIDChanges = false;
                    BTruckers::Server::Core::DBHandler* dbConnection = nullptr;

                public:
                    Preferences(BTruckers::Server::Core::DBHandler* db);
                    Preferences(BTruckers::Server::Core::DBHandler* db,std::string identifier, std::string value);

                    //override virtual functions
                    bool& IsLocked() override;
                    bool& IsInitialized() override;
                    bool& AllowUUIDChanges() override;
                    const std::string& GetTableName() override;
                    DB_FIELDS& GetDBFields() override;
                    BTruckers::Server::Core::DBHandler* GetConnection() override;

                    //custom functions
            };
        }
    }
}

#pragma once
#include "BTRCommon.h"
#include "DBHandler.h"
#include "models/BaseModel.h"
#include <unordered_map>

namespace BTruckers
{
    namespace Server
    {
        namespace Models
        {
            class Tokens : public BaseModel
            {
                private:
                    const std::string tableName = "sessions";
                    DB_FIELDS fields = {
                        {"uuid", BTruckers::Shared::Structures::TrackChanges{}},
                        {"user_uuid", BTruckers::Shared::Structures::TrackChanges{}},
                        {"identifier", BTruckers::Shared::Structures::TrackChanges{}},
                        {"validator", BTruckers::Shared::Structures::TrackChanges{}},
                        {"expiration_timestamp", BTruckers::Shared::Structures::TrackChanges{}},
                        {"creation_timestamp", BTruckers::Shared::Structures::TrackChanges{}}
                    };
                
                    bool lockClassChanges = false;
                    bool hasBeenInitialized = false;
                    bool allowUUIDChanges = false;
                    BTruckers::Server::Core::DBHandler* dbConnection = nullptr;
                public:
                    Tokens(BTruckers::Server::Core::DBHandler* db);
                    Tokens(BTruckers::Server::Core::DBHandler* db, std::string identifier, std::string value);

                    //override virtual functions
                    bool& IsLocked() override;
                    bool& IsInitialized() override;
                    bool& AllowUUIDChanges() override;
                    const std::string& GetTableName() override;
                    DB_FIELDS& GetDBFields() override;
                    BTruckers::Server::Core::DBHandler* GetConnection() override;

                    //custom functions
                    bool SetTime(int sessionDuration = 86400);
                    // bool CheckPassword(std::string plainText);
            };
        }
    }
}

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
            class Metrics : public BaseModel
            {
                private:
                    const std::string tableName = "metrics";
                    DB_FIELDS fields = {
                        {"uuid", BTruckers::Shared::Structures::TrackChanges{}},
                        {"user_uuid", BTruckers::Shared::Structures::TrackChanges{}},
                        {"speed", BTruckers::Shared::Structures::TrackChanges{}},
                        {"longitude", BTruckers::Shared::Structures::TrackChanges{}},
                        {"latitude", BTruckers::Shared::Structures::TrackChanges{}},
                    };
                
                    bool lockClassChanges = false;
                    bool hasBeenInitialized = false;
                    bool allowUUIDChanges = false;
                    BTruckers::Server::Core::DBHandler* dbConnection = nullptr;

                public:
                    Metrics(BTruckers::Server::Core::DBHandler* db);
                    Metrics(BTruckers::Server::Core::DBHandler* db,std::string identifier, std::string value);

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

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
            class Incidents : public BaseModel
            {
                private:
                    const std::string tableName = "incidents";
                    DB_FIELDS fields = {
                        {"uuid", BTruckers::Shared::Structures::TrackChanges{}},
                        {"timestamp", BTruckers::Shared::Structures::TrackChanges{}},
                        {"incident_type", BTruckers::Shared::Structures::TrackChanges{}},
                        {"reporter_uuid", BTruckers::Shared::Structures::TrackChanges{}},
                        {"location", BTruckers::Shared::Structures::TrackChanges{}},
                    };
                
                    bool lockClassChanges = false;
                    bool hasBeenInitialized = false;
                    bool allowUUIDChanges = false;
                    BTruckers::Server::Core::DBHandler* dbConnection = nullptr;

                public:
                    Incidents(BTruckers::Server::Core::DBHandler* db);
                    Incidents(BTruckers::Server::Core::DBHandler* db,std::string identifier, std::string value);

                    //override virtual functions
                    bool& IsLocked() override;
                    bool& IsInitialized() override;
                    bool& AllowUUIDChanges() override;
                    const std::string& GetTableName() override;
                    DB_FIELDS& GetDBFields() override;
                    BTruckers::Server::Core::DBHandler* GetConnection() override;
            };
        }
    }
}

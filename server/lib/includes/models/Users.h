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
            class Users : public BaseModel
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
                public:
                    Users();
                    Users(std::string identifier, std::string value);

                    //override virtual functions
                    bool& IsLocked() override;
                    bool& IsInitialized() override;
                    bool& AllowUUIDChanges() override;
                    const std::string& GetTableName() override;
                    DB_FIELDS& GetDBFields() override;
            };
        }
    }
}

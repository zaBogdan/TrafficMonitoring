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
            class BaseModel
            {
                private:
                    
                    static bool Populate(BTruckers::Server::Models::BaseModel& current, BTruckers::Server::Structures::SQLiteResponse& data);
                    bool Execute(std::string sql);

                public:

                    //virtual functions to override
                    virtual inline bool& IsLocked() = 0;
                    virtual inline bool& IsInitialized() = 0;
                    virtual inline bool& AllowUUIDChanges() = 0;
                    virtual inline const std::string& GetTableName() = 0;
                    virtual inline DB_FIELDS& GetDBFields() = 0;
                    virtual inline BTruckers::Server::Core::DBHandler* GetConnection() = 0;

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

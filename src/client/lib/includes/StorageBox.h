#pragma once
#include "BTRClient.h"
#include <unordered_map>


namespace BTruckers
{
    namespace Client
    {
        namespace Core
        {
            class StorageBox
            {
                private:
                    static std::unordered_map<std::string,std::string> storage;
                    StorageBox() = delete;
                public:
                    static bool SetItem(std::string key, std::string value);
                    static std::string GetItem(std::string key);

                    //this will work only on debug.
                    static void Print();
            };
        }
    }
}

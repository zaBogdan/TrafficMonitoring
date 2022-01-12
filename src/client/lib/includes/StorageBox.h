#pragma once
#include "BTRClient.h"
#include "PrimitiveTypes.h"
#include <unordered_map>
#include <fstream>
#include <sstream> 

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
                    static bool isInit;
                    StorageBox();
                public:
                    static bool SetItem(std::string key, std::string value);
                    static std::string GetItem(std::string key);

                    static void DumpToFile();
                    //this will work only on debug.
                    static void Print();
            };
        }
    }
}

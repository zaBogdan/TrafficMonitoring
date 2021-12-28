#pragma once
#include "BTRShared.h"


class PrimiteTypes{
    private:
        PrimiteTypes();
        static BTruckers::Shared::Structures::KeyValue DynamicParsing(std::string data);
    public:
        static std::string ToString(std::string data, std::string key = "");
        static BTruckers::Shared::Structures::KeyValue FromString(std::string data);

        static std::string ToDict(std::vector<std::string> data);
        static std::vector<BTruckers::Shared::Structures::KeyValue> FromDict(std::string data);

        static std::string ToInteger(int data, std::string key = "");
        static BTruckers::Shared::Structures::KeyValue FromInteger(std::string data);

        static std::string ToCoordinates(BTruckers::Shared::Structures::Cords data, std::string key = "");
        static BTruckers::Shared::Structures::KeyValue FromCoordinates(std::string data);
};
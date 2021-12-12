#pragma
#include "BTRShared.h"

class PrimiteTypes{
    private:
        PrimiteTypes();
        static BTRShared::Utils::KeyValue DynamicParsing(std::string data);
    public:
        static std::string ToString(std::string data, std::string key = "");
        static BTRShared::Utils::KeyValue FromString(std::string data);

        static std::string ToDict(std::vector<std::string> data);
        static std::vector<BTRShared::Utils::KeyValue> FromDict(std::string data);

        static std::string ToInteger(int data, std::string key = "");
        static BTRShared::Utils::KeyValue FromInteger(std::string data);

        static std::string ToCoordinates(BTRShared::Utils::Cords data, std::string key = "");
        static BTRShared::Utils::KeyValue FromCoordinates(std::string data);
};
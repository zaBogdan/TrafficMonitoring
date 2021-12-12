#pragma
#include "BTRShared.h"

class PrimiteTypes{
    private:
        PrimiteTypes();
    public:
        static std::string ToString(std::string data, std::string key = "");
        static std::string FromString(std::string data);

        static std::string ToDict(std::vector<std::string> data, std::string key = "");
        static std::string FromDict(std::string data);
};
#include "Utils.h"

namespace BTrucks{
    namespace Utils{
        std::string IntToHex(int x)
        {
            char *hexString = new char[3];
            if(x<16)
            {
                sprintf(hexString, "0%X",x);
            }else{
                sprintf(hexString, "%X",x);
            }
            return hexString;
        }

        int CheckResponse(int result, const char *errorMessage)
        {
            if(result == ERROR_SOCKET)
            {
                Logger::Error(errorMessage);
                exit(result);
            }
            return result;
        }
    }
}
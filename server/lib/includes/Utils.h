#pragma once
#include "BTRCommon.h"

namespace BTruckers
{
    namespace Server
    {
        namespace Utils
        {
            static inline std::string IntToHex(int x)
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

            static inline int CheckResponse(int result, const char *errorMessage)
            {
                if(result == ERROR_SOCKET)
                {
                    LOG_ERROR(errorMessage);
                    exit(result);
                }
                return result;
            }
        }
    }
}
// namespace BTrucks{
//     namespace Utils{
//         std::string IntToHex(int x);
//         int CheckResponse(int result, const char *errorMessage);
//     }
// }
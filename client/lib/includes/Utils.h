#pragma once
#include <stdio.h>
#include "Logger.h"
#include "BTRClient.h"


namespace BTruckers{
    namespace Client{
        namespace Utils{
            static inline int CheckResponse(int result, const char *errorMessage)
            {
                if(result == ERROR_SOCKET)
                {
                    perror(errorMessage);
                    exit(result);
                }
                return result;
            }

            static inline std::string IntToHex(int x)
            {
                char *hexString = new char[30];
                if(x<16)
                {
                    sprintf(hexString, "0%X",x);
                }else{
                    sprintf(hexString, "%X",x);
                }
                return hexString;
            }
        }
    }
}

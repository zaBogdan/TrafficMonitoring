#pragma once
#include <stdio.h>
#include "Logger.h"
#include "BTRClient.h"


namespace BTruckers{
    namespace Client{
        namespace Utils{
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

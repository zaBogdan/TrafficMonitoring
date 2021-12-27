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
            
            static inline void SignalHandler(int signal)
            {
                switch(signal)
                {
                    case SIGINT:
                        LOG_INFO("Received SIGINT. Starting the shutdown procedure...");
                        exit(0);

                    case SIGKILL:
                        LOG_INFO("Received SIGKILL. Starting the shutdown procedure...");
                        exit(0);
                    case SIGTERM:
                        LOG_INFO("Received SIGTERM. Starting the shutdown procedure...");
                        exit(0);
                    default:
                        LOG_INFO("The signal '%d' isn't yet treated.", signal);
                }
            }
        }
    }
}
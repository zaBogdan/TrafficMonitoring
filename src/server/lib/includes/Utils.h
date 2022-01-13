#pragma once
#include "BTRCommon.h"
#include <signal.h>
#include "Broadcaster.h"

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
                    BTruckers::Server::Core::serverRunning = false;
                    alarm(1);
                }
                return result;
            }
            
            static inline void SignalHandler(int signal)
            {
                switch(signal)
                {
                    case SIGINT:
                    case SIGKILL:
                    case SIGTERM:
                        LOG_INFO("Received SIGINT. Starting the shutdown procedure...");
                        BTruckers::Server::Core::serverRunning = false;
                        break;

                    default:
                        LOG_INFO("The signal '%d' isn't yet treated.", signal);
                }
            }

            static inline int GetSpeedLimit(int currentSpeed)
            {
                int possibleLimits[6] = {30, 50, 70, 90, 130};
                std::srand(currentSpeed);
                return possibleLimits[std::rand()%6];
            }
        }
    }
}
#pragma once
#include <cstring>
#include <string>
#include <random>
#include <ctime>
#include "BTRShared.h"
#include "constants.h"
#include "Logger.h"
#include "Utils.h"


namespace BTruckers
{
    namespace Client
    {
        //start client namespace code
        namespace Core
        {
            class Communcation;
            class CPV;
            class StorageBox;
        }

        namespace Utils{
            static inline std::string IntToHex(int x);
        }

        namespace Handler{
            std::string Create(std::string command, std::string tokens = "");
            std::string Parse(std::string command);
        }

        namespace Commands{
            //goto: sourceCommands for full function list.
        }
    
        namespace Sensors {
            
        }

        namespace Enums {
            //start enums code
            namespace CommandsCRC{
                enum Type: uint32_t{
                    //craft
                    AUTH = 0xF8DEB059,
                    AUTHENTICATE = 0xE500DB4,
                    LOGIN = 0xAA08CB10,
                    INCIDENT = 0x3D03A11A,
                    METRICS = 0x228AAAE7,
                    LOGOUT = 0x35CCF52F,
                    HELP = 0x8875CAC,
                    REGISTER = 0x5FF94014,
                    ENABLE_PREFERANCE = 0xF3A0C832,
                    DISABLE_PREFERANCE = 0x4F454D51,
                    SETSETTINGS = 0x694B4ADE,
                    RESTORE = 0x87D72FFF,
                    VIEW_SETTINGS = 0xFEFDAB8E,
                    
                    //parse
                    INVALIDATETOKENS = 0x94EE425,
                    SETTOKEN = 0X31CE86E1,
                    FAILEDCOMMAND = 0x33C9541B,
                    SUCCESSCOMMAND = 0x2BA9B036,
                    BROADCAST = 0x1900FE56,
                };
            }
            //end enums code
        }
        //end client namespace code
    }
}

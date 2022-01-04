#pragma once
#include <cstring>
#include <string>
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
    
        namespace Enums {
            //start enums code
            namespace CommandsCRC{
                enum Type: uint32_t{
                    //craft
                    AUTH = 0xF8DEB059,
                    AUTHENTICATE = 0xE500DB4,
                    LOGIN = 0xAA08CB10,

                    INCIDENT = 0x3D03A11A,

                    LOGOUT = 0x35CCF52F,

                    //parse
                    SETTOKEN = 0X31CE86E1,
                    FAILEDCOMMAND = 0x33C9541B,
                    SUCCESSCOMMAND = 0x2BA9B036
                };
            }
            //end enums code
        }
        //end client namespace code
    }
}

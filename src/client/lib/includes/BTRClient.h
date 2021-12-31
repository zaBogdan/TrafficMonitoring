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
                    AUTH = 0xf8deb059,
                    AUTHENTICATE = 0xe500db4,
                    LOGIN = 0xaa08cb10,

                    INCIDENT = 0x3d03a11a,

                    LOGOUT = 0x35ccf52f,
                };
            }
            //end enums code
        }
        //end client namespace code
    }
}

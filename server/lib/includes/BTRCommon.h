#pragma once
#include <iostream>
#include <string>
#include "constants.h"
#include "Logger.h"
#include "Utils.h"

namespace BTruckers
{
    namespace Server
    {
        //start server code

        namespace Core
        {
            class Server;
            class Tokens;
            class CPV;
            class DBHandler;
        }

        namespace Utils
        {
            static inline std::string IntToHex(int x);
            static inline int CheckResponse(int result, const char *errorMessage);
        }

        namespace Commands
        {
            //goto: sourceCommands.h
        }
        
        namespace Models
        {
            //insert all the database models that are to be used
            class Users;
        }

        namespace Enums
        {
            //start enums code
            namespace CommandsCRC
            {
                enum Type: uint32_t
                {
                    AUTHENTICATE = 0xE500DB4,

                    INCIDENT = 0x3d03a11a,

                    LOGOUT = 0x35ccf52f,
                };
            }
            //end enums code
        }
        
        
        
        //end server code
    }
}
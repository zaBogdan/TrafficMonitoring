#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
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
            class SocketPair;

            //continuing the namespace after structures
            // add a function that will write some text to all the sockets
            //the text will be decided at calltime (it must be a dict of some type)
            //for simplicity add event1,2,3 etc. (to not implement an array)
        }

        namespace Utils
        {
            static inline std::string IntToHex(int x);
            static inline int CheckResponse(int result, const char *errorMessage);
            static inline void SignalHandler(int signal);
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

        namespace Structures
        {
            struct SQLiteResponse
            {
                int count = 0;
                std::vector<BTruckers::Shared::Structures::KeyValue> values;
            };
            
            struct SocketData
            {
                int socketId;
                std::string userUUID;
            };

            struct Thread
            {
                int idx = 0;
                int count = 0;
                int serverSocket = 0;
                fd_set currentSockets;
                std::vector<SocketData> sockets;
            };
        }

        namespace Enums
        {
            //start enums code
            namespace CommandsCRC
            {
                enum Type: uint32_t
                {
                    AUTHENTICATE = 0xE500DB4,

                    INCIDENT = 0x3D03A11A,

                    LOGOUT = 0x35ccf52f,
                };
            }
            //end enums code
        }
        
        
        
        //end server code
    }
}
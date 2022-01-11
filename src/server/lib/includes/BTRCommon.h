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
        }

        namespace Utils
        {
            static inline std::string IntToHex(int x);
            static inline int CheckResponse(int result, const char *errorMessage);
            static inline void SignalHandler(int signal);
        }

        namespace Broadcast
        {
            void BroadcastMessage(std::string cmd, std::string payload, uint8_t cond);
            bool IsConditionSatisfied(std::string uuid, BTruckers::Server::Core::DBHandler *db);
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

                    INCIDENT = 0x3D03A11A,
                    
                    BROADCAST = 0x9BF17CF5,

                    LOGOUT = 0x35ccf52f,
                };
            }

            namespace BroadcastConditions
            {
                enum Type: uint8_t
                {
                    NONE = 0,
                    SELECTED_ENTERTAINMENT = 1,

                };
            }
            //end enums code
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

            struct BroadcasterMessages{
                std::string message;
                Enums::BroadcastConditions::Type cond;
            };
        }

        
        //end server code
    }
}
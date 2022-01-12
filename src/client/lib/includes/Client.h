#pragma once
#include "BTRClient.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

namespace BTruckers
{
    namespace Client
    {
        namespace Core
        {
            class Communcation{
                private:
                    int clientSocket;
                    bool InitiateConnection(const char* ip, int port);
                public:
                    Communcation(const char* ip, int port);
                    ~Communcation();
                    std::string ReadFromCLI();
                    int GetClientSocket();
            };
        }
    }
}
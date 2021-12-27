#pragma once
#include "BTRCommon.h"
#include <sys/socket.h>
#include <unistd.h>


namespace BTruckers
{
    namespace Server
    {
        namespace Core
        {
            class SocketPair
            {
                private:
                    int sockets[2];
                    int mode;
                    const int parentSocket = 0;
                    const int childSocket = 1;
                public: 
                    SocketPair();
                    ~SocketPair();
                    void SelectMode(bool isParent = true);
                    std::string Receive();
                    void Send(std::string data);
            };
        }
    }
}

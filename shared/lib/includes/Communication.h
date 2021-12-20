#pragma once
#include "BTRShared.h"
#include "Logger.h"
#include <unistd.h>

namespace BTruckers
{
    namespace Shared
    {
        namespace TCPCommunication
        {
            bool Send(int socket, std::string message);
            std::string Receive(int socket);
        }
    }
}
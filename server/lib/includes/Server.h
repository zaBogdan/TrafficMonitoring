#pragma once
#include "BTRCommon.h"
#include "Logger.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

namespace BTrucks{
    class Server{
        private:
            int serverSocket;
            const int ERROR_SOCKET = -1;
            bool Setup(int PORT, int BACKLOG);
            int CheckResponse(int result, const char *errorMessage);
        public:
            Server(int PORT = RUNNING_PORT, int BACKLOG = BACK_LOG);
            int InitiateConnection();
            int& getServerSocket();
            ~Server();
    };
}
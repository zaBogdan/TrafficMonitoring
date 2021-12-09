#pragma once
#include "BTRCommon.h"
#include "Utils.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

namespace BTrucks{
    class Server{
        private:
            int serverSocket;
            bool Setup(int PORT, int BACKLOG);
        public:
            Server(int PORT = RUNNING_PORT, int BACKLOG = BACK_LOG);
            int InitiateConnectionWithClient();
            int& getServerSocket();
            ~Server();
    };
}
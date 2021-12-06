#pragma once
#include "BTrucks.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include "../../../shared/lib/includes/Logger.h"

namespace BTrucks{
    class Server{
        private:
            int serverSocket;
            const int ERROR_SOCKET = -1;
            bool Setup();
            int CheckResponse(int result, const char *errorMessage);
        public:
            Server();
            int InitiateConnection();
            int& getServerSocket();
            ~Server();
    };
}
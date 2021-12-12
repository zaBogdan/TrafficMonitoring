#pragma once
#include "BTRClient.h"
#include "Utils.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

namespace BTrucks{
    class Client{
        private:
            int clientSocket;
            bool InitiateConnection(const char* ip, int port);
        public:
            Client(const char* ip, int port);
            std::string ReadFromCLI();
    };
}
#pragma once
#include "BTrucks.h"
// #include "Logger.h"

namespace BTrucks{
    class Server{
        private:
            void Setup();
        public:
            Server();
            void InitiateConnection();
            ~Server();
    };
}
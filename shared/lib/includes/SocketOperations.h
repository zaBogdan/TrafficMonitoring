#pragma once
#include <string>
#include <iostream>

class SocketOperations{
    private:
        SocketOperations();
        static SocketOperations* instance;
    public:
        static SocketOperations* GetInstance();
        static std::string GetMessage(int workingSocket);
        static bool SendMessage(int workingSocket,std::string msg);
};
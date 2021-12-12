#pragma once
#include <string>
#include <iostream>
#include "BTRShared.h"
#include "Logger.h"
#include "Commands.h"

class Message{
    private:
        Message();

        static Message* instance;
    public:
        static Message* GetInstance();
        static std::string Format(std::string msg);
        static char* Parse(const char* msg);
};
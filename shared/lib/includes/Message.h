#pragma once
#include <string>
#include <iostream>
#include "BTRShared.h"
#include "Logger.h"

class Message{
    private:
        Message();

        static Message* instance;
    public:
        static Message* GetInstance();
        static std::string Format(std::string msg);
        static BTruckers::Shared::Structures::Message Parse(std:: string command);
};
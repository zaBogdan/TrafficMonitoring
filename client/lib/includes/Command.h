#pragma once
#include "BTRClient.h"
#include "Logger.h"
#include "sharedCommands.h"
#include "sourceCommands.h"

namespace BTruckers{
    namespace Client{
        namespace CommandHandler{
            std::string Create(std::string command, std::string tokens = "");
            // std::string Parse(std::string command);
        }
    }
}
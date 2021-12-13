#pragma once
#include "BTRClient.h"
#include "Logger.h"
#include "sharedCommands.h"
#include "sourceCommands.h"

namespace BTrucks{
    namespace CommandHandler{
        std::string Evaluate(std::string command, std::string tokens = "");
        // std::string Parse(std::string command);
    }
}
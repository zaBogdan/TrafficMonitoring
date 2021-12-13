#pragma once
#include "BTRClient.h"
#include "Logger.h"
#include "Utils.h"
#include "sharedCommands.h"
#include "sourceCommands.h"

namespace BTrucks{
    namespace CommandHandler{
        std::string Create(std::string command, std::string tokens = "");
        // std::string Parse(std::string command);
    }
}
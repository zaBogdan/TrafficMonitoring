#pragma once
#include "BTRCommon.h"
#include "BTRShared.h"
#include "Message.h"
#include "sourceCommands.h"

namespace BTrucks{
    namespace CommandHandler{
        // std::string Create(std::string command);
        std::string Handle(std::string command);        
    }
}
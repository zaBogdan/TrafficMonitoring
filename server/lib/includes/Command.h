#pragma once
#include "BTRCommon.h"
#include "BTRShared.h"

namespace BTrucks{
    namespace CommandHandler{
        // std::string Create(std::string command);
        std::string Handle(std::string command);
        BTRShared::Utils::MessageFormat Parse(std::string command);
        
    }
}
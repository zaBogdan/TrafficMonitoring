#pragma once
#include "BTRShared.h"
#include "Logger.h"

namespace BTRShared{
    namespace Commands{
        std::string HandleCommand(const char* command, const char* payload);
        std::string Evaluate(std::string command);


    }
}
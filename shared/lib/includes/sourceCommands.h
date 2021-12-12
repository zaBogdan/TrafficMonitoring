#pragma once
#include "BTRShared.h"
#include "PrimitiveTypes.h"

namespace BTRShared {
    namespace Command{
        std::string CreateAuthenticateCommand(std::string payload);
        std::string ParseAuthenticateCommand(std::string payload);

        std::string CreateIncidentCommand(std::string payload);
        std::string ParseIncidentCommand(std::string payload);
    }
}
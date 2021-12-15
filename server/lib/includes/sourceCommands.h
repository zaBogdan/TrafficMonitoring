#pragma once
#include "BTRCommon.h"
#include "BTRShared.h"
#include "PrimitiveTypes.h"

namespace BTrucks {
    namespace Commands{
        std::string HandleAuthenticateCommand(std::string payload);
        std::string HandleValidateTokensCommand(std::string payload);
        std::string ParseIncidentCommand(std::string payload);
    }
}
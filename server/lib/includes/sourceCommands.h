#pragma once
#include "BTRCommon.h"
#include "BTRShared.h"
#include "PrimitiveTypes.h"

namespace BTrucks {
    namespace Commands{
        std::string ParseAuthenticateCommand(std::string payload);
        std::string ParseIncidentCommand(std::string payload);
    }
}
#pragma once
#include "BTRClient.h"
#include "BTRShared.h"
#include "PrimitiveTypes.h"

namespace BTrucks {
    namespace Commands{
        std::string CreateAuthenticateCommand(std::string payload);

        std::string CreateIncidentCommand(std::string payload);
    }
}
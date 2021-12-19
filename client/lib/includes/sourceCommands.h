#pragma once
#include "BTRClient.h"
#include "BTRShared.h"
#include "PrimitiveTypes.h"

namespace BTruckers{
    namespace Client{
        namespace Commands{
            //start commands code
            std::string CreateAuthenticateCommand(std::string payload);
            std::string CreateIncidentCommand(std::string payload);
            //end commands code
        }
    }
}
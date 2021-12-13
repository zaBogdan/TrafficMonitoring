#pragma once
#include "BTRShared.h"
#include "PrimitiveTypes.h"
#define INCIDENT_COMMAND "Incident"
#define AUTHENTICATE_COMMAND "Authenticate"

namespace BTRShared {
    namespace Command{
        std::string CreateResponseCommand(std::string payload);
        std::string ParseResponseCommand(std::string payload);
    }
}
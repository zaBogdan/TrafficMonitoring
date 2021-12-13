#pragma once
#include "BTRShared.h"
#include "PrimitiveTypes.h"

namespace BTRShared {
    namespace Command{
        std::string CreateResponseCommand(std::string payload);
        std::string ParseResponseCommand(std::string payload);
    }
}
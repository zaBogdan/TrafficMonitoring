#pragma once
#include "BTRShared.h"
#include "PrimitiveTypes.h"

namespace BTruckers {
    namespace Shared{
        namespace Commands{
            std::string CreateResponseCommand(std::string payload);
            std::string ParseResponseCommand(std::string payload);
        }
    }
}
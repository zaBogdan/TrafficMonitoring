#pragma once
#include "BTRCommon.h"

namespace BTrucks{
    namespace Utils{
        std::string IntToHex(int x);
        int CheckResponse(int result, const char *errorMessage);
    }
}
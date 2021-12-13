#pragma once
#include "BTRClient.h"

namespace BTrucks{
    namespace Utils{
        int CheckResponse(int result, const char *errorMessage);
        std::string IntToHex(int x);
    }
}
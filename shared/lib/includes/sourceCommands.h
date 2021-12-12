#pragma once
#include "BTRShared.h"
#include "BTRShared.h"

namespace BTRShared {
    namespace Command{
        std::string CreateAuthenticateCommand(std::string payload);
        std::string ParseAuthenticateCommand(std::string payload);
    }
}
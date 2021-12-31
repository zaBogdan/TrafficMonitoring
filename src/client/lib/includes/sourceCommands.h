#pragma once
#include "BTRClient.h"
#include "BTRShared.h"
#include "PrimitiveTypes.h"

namespace BTruckers{
    namespace Client{
        namespace Commands{
            //handler
            std::string Handler(BTruckers::Shared::Structures::Message message);

            //start commands code
            namespace Handle
            {
                std::string SetTokens(std::string payload);
            }

            namespace Craft
            {
                std::string Authentication(std::string payload);
            }
            //end commands code
        }
    }
}
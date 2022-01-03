#pragma once
#include "BTRClient.h"
#include "BTRShared.h"
#include "PrimitiveTypes.h"
#include "StorageBox.h"

namespace BTruckers{
    namespace Client{
        namespace Commands{
            //handler
            std::string HandleResponse(BTruckers::Shared::Structures::Message message, bool isRequest = true);

            //start commands code
            namespace Handle
            {
                std::string SetTokens(std::string payload);
                std::string CommandFailed(std::string payload);
            }

            namespace Craft
            {
                std::string Authentication(std::string payload);
                std::string ReportIncident(std::string payload);
            }
            //end commands code
        }
    }
}
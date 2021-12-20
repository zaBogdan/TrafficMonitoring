#pragma once
#include "BTRCommon.h"
#include "BTRShared.h"
#include "PrimitiveTypes.h"

namespace BTruckers
{
    namespace Server
    {
        namespace Commands{
            //handler
            std::string Handler(BTruckers::Shared::Structures::Message message);

            //start commands code
            std::string HandleAuthenticateCommand(std::string payload);
            std::string HandleValidateTokensCommand(std::string payload);
            std::string ParseIncidentCommand(std::string payload);
            //end commands code
        }
    }
}

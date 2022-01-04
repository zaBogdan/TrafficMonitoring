#pragma once
#include "BTRClient.h"
#include "BTRShared.h"
#include "VirtualCPV.h"
#include "Logger.h"
#include "sharedCommands.h"
#include "clientCommands.h"

namespace BTruckers
{
    namespace Client
    {
        namespace Core
        {
            class CPV : public BTruckers::Shared::Core::CPV
            {
                public: 
                    CPV() = default;
                    BTruckers::Shared::Structures::Message Craft(std::string payload);
                    BTruckers::Shared::Structures::Message Parse(std::string payload);
                    bool Validate(std::string payload);     
            };
        }
    }
}
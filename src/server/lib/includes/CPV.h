#pragma once
#include "BTRCommon.h"
#include "BTRShared.h"
#include "VirtualCPV.h"
#include "Logger.h"
#include "sharedCommands.h"
#include "sourceCommands.h"

namespace BTruckers
{
    namespace Server
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
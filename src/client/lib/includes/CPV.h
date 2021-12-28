#pragma once
#include "BTRClient.h"
#include "BTRShared.h"
#include "VirtualCPV.h"
#include "Logger.h"
#include "sharedCommands.h"
#include "sourceCommands.h"

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
                    std::string Craft(std::string payload);
                    BTruckers::Shared::Structures::Message Parse(std::string payload);
                    bool Validate(std::string payload);     
            };
        }
    }
}
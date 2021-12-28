#pragma once
#include <string>
#include "BTRShared.h"
#include "Logger.h"

namespace BTruckers
{
    namespace Shared 
    {
        namespace Core
        {
            class CPV
            {
                public:
                    virtual std::string Craft(std::string payload) = 0;
                    virtual BTruckers::Shared::Structures::Message Parse(std::string payload) = 0;
                    virtual bool Validate(std::string payload) = 0;        
            };
        }
    }
}
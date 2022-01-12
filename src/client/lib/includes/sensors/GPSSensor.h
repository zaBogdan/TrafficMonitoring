#pragma once
#include "BTRClient.h"

namespace BTruckers
{
    namespace Client
    {
        namespace Sensors
        {
            class GPS
            {
                private:
                    BTruckers::Shared::Structures::Cords position;

                    void Update();
                public:
                    GPS();
                    BTruckers::Shared::Structures::Cords Read();
            };
        }
    }
}

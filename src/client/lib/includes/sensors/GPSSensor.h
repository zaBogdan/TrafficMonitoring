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
                    static BTruckers::Shared::Structures::Cords position;
                    static bool isInit;
                    static void Update();
                public:
                    GPS();
                    static BTruckers::Shared::Structures::Cords Read();
            };
        }
    }
}

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
                    long long longitute;
                    long long latitude;

                    void Update();
                public:
                    GPS();
                    std::pair<long long, long long> Read();
            };
        }
    }
}

#pragma once
#include "BTRClient.h"

namespace BTruckers
{
    namespace Client
    {
        namespace Sensors
        {
            class Speed
            {
                private:
                    int speedData;
                    
                    void Update();
                public:
                    Speed();
                    int Read();
            };
        }
    }
}

#pragma once
#include "BTRCommon.h"
#include <queue>

namespace BTruckers
{
    namespace Server
    {
        namespace Core
        {
            class Broadcaster
            {
                private:
                    Broadcaster();
                    static bool isInit;
                public:
                    static pthread_mutex_t broadcasterLock;
                    static pthread_cond_t waitForData;
                    static std::queue<std::string> broadcasterQueue;
                    
                    
                    static void Init();
                    static void PushMessageToQueue(std::string message);

            };

        }
    }
}
#pragma once
#include <iostream>
#include <string>

namespace BTrucks
{
    const unsigned int runningPort = 1337;
    class Server;
    
    namespace Utils{
        namespace LoggingLevel{
            enum Type : unsigned int{
                CRITICAL = 50,
                ERROR = 40,
                WARNING = 30,
                INFO = 20,
                DEBUG = 10
            };
        }
    }
}
#pragma once
#include <string>

namespace BTrucksShared
{
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
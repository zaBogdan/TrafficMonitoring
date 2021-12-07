#pragma once
#include <string>
#include <time.h>


namespace BTrucksShared
{
    namespace Utils{
        namespace LoggingLevel{
            enum Type : unsigned int{
                CRITICAL =  50,
                ERROR =     40,
                WARNING =   30,
                INFO =      20,
                DEBUG =     10
            };
        }
        
        static std::string CurrentDateTime()
        {
            time_t     now;
            struct tm  *timeStruct;
            char       buf[80];
            time(&now);
            timeStruct = localtime(&now);
            strftime(buf, sizeof(buf), "%Y/%m/%d %X", timeStruct);
            return buf;
        }
    }
}
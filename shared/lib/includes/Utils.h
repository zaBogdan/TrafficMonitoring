#pragma once
#include "BTRShared.h"

namespace BTruckers{
    namespace Shared{
        namespace Utils{

            static inline time_t GetUNIXTimestamp()
            {
                std::time_t time = std::time(0);
                return time;
            }

            static inline std::string CurrentDateTime()
            {
                time_t     now;
                struct tm  *timeStruct;
                char       buf[80];
                time(&now);
                timeStruct = localtime(&now);
                strftime(buf, sizeof(buf), "%Y/%m/%d %X", timeStruct);
                return buf;
            }

            static inline uint32_t CRCValue(std::string s)
            {
                uint32_t crc=0xFFFFFFFF;
                size_t n = s.length();

                for(size_t i=0;i<n;i++) {
                    char ch=s[i];
                    for(size_t j=0;j<8;j++) {
                        uint32_t b=(ch^crc)&1;
                        crc>>=1;
                        if(b) crc=crc^0xEDB88320;
                        ch>>=1;
                    }
                }
                
                return ~crc;
            }
            
            static inline int CheckResponse(int result, const char *errorMessage)
            {
                if(result == ERROR_SOCKET)
                {
                    perror(errorMessage);
                    exit(result);
                }
                return result;
            }
        }
    }
}
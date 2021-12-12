#pragma once
#include <string>
#include <time.h>
#include <stddef.h>
#include <stdint.h>
#include "sources.h"

namespace BTRShared
{
    namespace Utils{
        
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
        static uint32_t CRCValue(const char *s, size_t n) {
            uint32_t crc=0xFFFFFFFF;

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

        struct TokenData {
            std::string identifier, validator;
        };
        struct MessageFormat {
            TokenData token;
            std::string command, payload;
        };
    }
}
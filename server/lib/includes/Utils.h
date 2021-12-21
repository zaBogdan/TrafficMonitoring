#pragma once
#include "BTRCommon.h"

namespace BTruckers
{
    namespace Server
    {
        namespace Utils
        {
            static inline std::string IntToHex(int x)
            {
                char *hexString = new char[3];
                if(x<16)
                {
                    sprintf(hexString, "0%X",x);
                }else{
                    sprintf(hexString, "%X",x);
                }
                return hexString;
            }

            static inline int CheckResponse(int result, const char *errorMessage)
            {
                if(result == ERROR_SOCKET)
                {
                    LOG_ERROR(errorMessage);
                    exit(result);
                }
                return result;
            }

            static inline std::string FormatFromString(std::string format, std::string substitution, ...)
            {
                size_t pos = format.find(substitution);
                va_list args;
                va_start(args, substitution);
                while(pos != std::string::npos)
                {
                    std::string arg = va_arg(args, char*);
                    format.erase(pos, substitution.length());
                    format.insert(pos, arg);
                    pos = format.find(substitution);
                }
                va_end(args);
                return format;
            }

            static inline bool AddNewChar(std::string& format, std::string delimiter, std::string character)
            {
                size_t pos = format.find(delimiter);
                while(pos != std::string::npos)
                {
                    format.insert(pos+1, character);
                    pos = format.find(delimiter,pos+delimiter.length()*2+1);
                }
                return true;
            }
        }
    }
}
// namespace BTrucks{
//     namespace Utils{
//         std::string IntToHex(int x);
//         int CheckResponse(int result, const char *errorMessage);
//     }
// }
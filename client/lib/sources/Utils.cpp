#include "Utils.h"

int BTrucks::Utils::CheckResponse(int result, const char *errorMessage)
{
    if(result == ERROR_SOCKET)
    {
        Logger::Error(errorMessage);
        exit(result);
    }
    return result;
}

std::string BTrucks::Utils::IntToHex(int x)
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
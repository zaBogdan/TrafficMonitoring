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
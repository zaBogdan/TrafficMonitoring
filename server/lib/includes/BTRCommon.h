#pragma once
#include <iostream>
#include <string>
#include "constants.h"
#include "Logger.h"
#include "Utils.h"

namespace BTrucks
{
    class Server;
    class Tokens;
    namespace Command {
        enum Type: uint32_t{
            AUTHENTICATE = 0xE500DB4,

            INCIDENT = 0x3d03a11a,

            LOGOUT = 0x35ccf52f,

        };
    }
}
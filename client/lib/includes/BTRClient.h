#pragma once
#include <cstring>
#include "constants.h"
#include "Logger.h"

namespace BTrucks{
    class Client;

    namespace Utils{
        namespace Command {
            enum Type: uint32_t{
                AUTH = 0xf8deb059,
                AUTHENTICATE = 0xe500db4,
                LOGIN = 0xaa08cb10,

                INCIDENT = 0x3d03a11a,

                LOGOUT = 0x35ccf52f,

            };
        }
    }
}
#pragma once
#include "BTRCommon.h"
#include "Utils.h"
#include <openssl/rand.h>
#include <openssl/err.h>
#include <openssl/sha.h>
#include <random>
#include <sstream>
#include <iomanip>

namespace BTruckers
{
    namespace Server
    {
        namespace Core
        {
            class Tokens
            {
                public:
                    Tokens();
                    static std::string Generate(int tokenSize = TOKEN_SIZE);
                    static std::string UUID();
                    static std::string SHA256(std::string string);
            };
        }
    }
}
#pragma once
#include "BTRCommon.h"
#include "Utils.h"
#include <openssl/rand.h>
#include <openssl/err.h>

namespace BTruckers
{
    namespace Server
    {
        namespace Core
        {
            class Tokens
            {
                private:
                    const int tokenLength = TOKEN_SIZE;
                public:
                    Tokens();
                    std::string Generate();
            };
        }
    }
}
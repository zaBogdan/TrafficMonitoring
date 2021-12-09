#include "BTRCommon.h"
#include <openssl/rand.h>
#include <openssl/err.h>
#include <iostream>

namespace BTrucks{
    class Tokens{
        private:
            const int tokenLength = 16;
        public:
            Tokens();
            std::string Generate();
    };
}
#include "BTRCommon.h"
#include "Utils.h"
#include <openssl/rand.h>
#include <openssl/err.h>
#include <iostream>

namespace BTrucks{
    class Tokens{
        private:
            const int tokenLength = TOKEN_SIZE;
        public:
            Tokens();
            std::string Generate();
    };
}
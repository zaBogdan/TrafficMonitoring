#include "BTRCommon.h"
#include "Utils.h"
#include <openssl/rand.h>
#include <openssl/err.h>
#include <iostream>

namespace BTrucks{
    class Tokens{
        private:
            const int tokenLength = 8;
        public:
            Tokens();
            std::string Generate();
    };
}
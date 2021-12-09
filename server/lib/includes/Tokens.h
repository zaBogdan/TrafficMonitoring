#include "BTrucks.h"
#include <openssl/rand.h>


namespace BTrucks{
    class Tokens{
        private:
            const int tokenLength = 16;
        public:
            Tokens();
            std::string Generate();
    };
}
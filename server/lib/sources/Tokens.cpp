#include "Tokens.h"

BTrucks::Tokens::Tokens()
{

}

std::string BTrucks::Tokens::Generate()
{
    unsigned char *token = new unsigned char[this->tokenLength];
    int rc = RAND_bytes(token, sizeof(unsigned char)*sizeof(token));
    std::cout << token << '\n';
    return "";
    // return reinterpret_cast<char const*>(token);
}
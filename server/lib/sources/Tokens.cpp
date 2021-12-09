#include "../includes/Tokens.h"

BTrucks::Tokens::Tokens()
{

}

std::string BTrucks::Tokens::Generate()
{
    unsigned char token[30];
    RAND_bytes(token, this->tokenLength);
    return reinterpret_cast<char const*>(token);
}
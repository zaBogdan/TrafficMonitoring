#include "Tokens.h"

BTrucks::Tokens::Tokens()
{

}

std::string BTrucks::Tokens::Generate()
{
    unsigned char *token = new unsigned char[this->tokenLength+1];
    int rc = RAND_bytes(token, sizeof(unsigned char)*sizeof(token));
    std::string hexBytes;
    for(int i=0;i<this->tokenLength;i++)
    {
        hexBytes += BTrucks::Utils::IntToHex(token[i]);
    }
    return hexBytes;
}
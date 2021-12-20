#include "Tokens.h"

BTruckers::Server::Core::Tokens::Tokens()
{

}

std::string BTruckers::Server::Core::Tokens::Generate()
{
    unsigned char *token = new unsigned char[this->tokenLength+1];
    int rc = RAND_bytes(token, sizeof(unsigned char)*sizeof(token));
    std::string hexBytes;
    for(int i=0;i<this->tokenLength;i++)
    {
        hexBytes += BTruckers::Server::Utils::IntToHex(token[i]);
    }
    return hexBytes;
}
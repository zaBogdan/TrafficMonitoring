#include "Tokens.h"

BTruckers::Server::Core::Tokens::Tokens()
{

}

std::string BTruckers::Server::Core::Tokens::Generate(int tokenSize)
{
    unsigned char *token = new unsigned char[tokenSize+1];
    int rc = RAND_bytes(token, sizeof(unsigned char)*sizeof(token));
    std::string hexBytes;
    for(int i=0;i<tokenSize;i++)
    {
        hexBytes += BTruckers::Server::Utils::IntToHex(token[i]);
    }
    return hexBytes;
}

//code from https://stackoverflow.com/questions/24365331/how-can-i-generate-uuid-in-c-without-using-boost-library
std::string BTruckers::Server::Core::Tokens::UUID()
{
    static std::random_device              rd;
    static std::mt19937                    gen(rd());
    static std::uniform_int_distribution<> dis(0, 15);
    static std::uniform_int_distribution<> dis2(8, 11);

    std::stringstream ss;
    int i;
    ss << std::hex;
    for (i = 0; i < 8; i++) {
        ss << dis(gen);
    }
    ss << "-";
    for (i = 0; i < 4; i++) {
        ss << dis(gen);
    }
    ss << "-4";
    for (i = 0; i < 3; i++) {
        ss << dis(gen);
    }
    ss << "-";
    ss << dis2(gen);
    for (i = 0; i < 3; i++) {
        ss << dis(gen);
    }
    ss << "-";
    for (i = 0; i < 12; i++) {
        ss << dis(gen);
    };
    return ss.str();
}

// https://stackoverflow.com/questions/57063250/can-i-create-openssl-ec-key-when-i-have-public-key-in-hex-format-using-c
std::string BTruckers::Server::Core::Tokens::SHA256(std::string str)
{
    EVP_MD_CTX* context = EVP_MD_CTX_new();

    if(context != NULL)
    {
        if(EVP_DigestInit_ex(context, EVP_sha256(), NULL))
        {
            if(EVP_DigestUpdate(context, str.c_str(), str.length()))
            {
                unsigned char hash[EVP_MAX_MD_SIZE];
                unsigned int lengthOfHash = 0;

                if(EVP_DigestFinal_ex(context, hash, &lengthOfHash))
                {
                    std::stringstream ss;
                    for(unsigned int i = 0; i < lengthOfHash; ++i)
                    {
                        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
                    }
                    EVP_MD_CTX_free(context);
                    return ss.str();
                }
            }
        }

    }
    return "";
}
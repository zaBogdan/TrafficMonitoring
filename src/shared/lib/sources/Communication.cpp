#include "protocols/TCP.h"

bool BTruckers::Shared::Protocols::TCP::Send(int socket,std::string msg)
{
    LOG_DEBUG("Starting to format the message. Adding the prefix");
    if(msg == "")
    {
        return false;
    }
    
    msg = MESSAGE_SEPARATOR + msg;
    
    //prefixing the message with it's length
    std::string messageLength = std::to_string(msg.length());
    messageLength.insert(0, 4-messageLength.length(),'0');
    msg = messageLength+msg;

    const char* cstrMsg = msg.c_str();
    LOG_DEBUG("The new message is: %s", cstrMsg);
    int respCode = write(socket, cstrMsg, msg.length()*sizeof(char));
    if(respCode < 0)
    {
        LOG_WARNING("Failed to send message to socket '%d'", socket);
        return false;
    }

    LOG_DEBUG("Successfully sent to the server");
    return true;
}

std::string BTruckers::Shared::Protocols::TCP::Receive(int socket)
{
    LOG_DEBUG("Reading the first 4 bytes of the message");
    char messagePrefix[5];
    int respCode = read(socket, messagePrefix, 4*sizeof(messagePrefix[0]));

    if(respCode < 0){
        if(respCode == EINTR)
        {
            LOG_WARNING("Connection with socket '%d' will be closed. (got EINTR)");
            return "";
        }
        return "";
    }
    LOG_CRITICAL("The response of read is: %d", respCode);

    messagePrefix[4] = '\0'; //makeing it a valid cstring

    size_t msgLen = std::atoi(messagePrefix);
    if(msgLen == 0)
        return "";
    LOG_DEBUG("Reading the next %u bytes of the message", msgLen);
    char *actualMessage = new char[msgLen+1];
    BTruckers::Shared::Utils::CheckResponse(read(socket, actualMessage, msgLen*sizeof(actualMessage[0])), "Failed to read from the socket.");
    actualMessage[msgLen] = '\0';

    LOG_DEBUG("Final message is: %s", actualMessage);
    return std::string(actualMessage);
}
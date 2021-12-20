#include "Communication.h"

bool BTruckers::Shared::TCPCommunication::Send(int socket,std::string msg)
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

    //transforming it to c string
    const char* cstrMsg = msg.c_str();
    LOG_DEBUG("The new message is: %s", cstrMsg);
    BTruckers::Shared::Utils::CheckResponse(write(socket, cstrMsg, msg.length()*sizeof(char)), "Failed to send the message.");
    LOG_DEBUG("Successfully sent to the server");
    return true;
}

std::string BTruckers::Shared::TCPCommunication::Receive(int socket)
{
    LOG_DEBUG("Reading the first 4 bytes of the message");
    char messagePrefix[5];
    BTruckers::Shared::Utils::CheckResponse(read(socket, messagePrefix, 4*sizeof(messagePrefix[0])), "Failed to read from the socket.");
    messagePrefix[4] = '\0'; //makeing it a valid cstring

    //transforming it to integer
    size_t msgLen = std::atoi(messagePrefix);
    LOG_DEBUG("Reading the next %u bytes of the message", msgLen);
    //reading the next bytes
    char *actualMessage = new char[msgLen+1];
    BTruckers::Shared::Utils::CheckResponse(read(socket, actualMessage, msgLen*sizeof(actualMessage[0])), "Failed to read from the socket.");
    //making it a valid cstring
    actualMessage[msgLen] = '\0';

    LOG_DEBUG("Final message is: %s", actualMessage);
    //returing a std::string
    return std::string(actualMessage);
}
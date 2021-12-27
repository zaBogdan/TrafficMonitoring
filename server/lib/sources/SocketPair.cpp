#include "SocketPair.h"

BTruckers::Server::Core::SocketPair::SocketPair()
{
    if(socketpair(AF_UNIX, SOCK_STREAM, 0, this->sockets)==-1)
    {
        LOG_ERROR("Failed to create a named pipe. Exiting");
        exit(31);
    }
}
void BTruckers::Server::Core::SocketPair::SelectMode(bool isParent)
{
    this->mode = isParent==true ? this->parentSocket : this->childSocket;
}


std::string BTruckers::Server::Core::SocketPair::Receive()
{
    char buf[256];
    LOG_DEBUG("[SocketPair::Receive] Waiting for data to read");

    char msgLen[5];
    do{
        int prefixData = read(this->sockets[this->mode],msgLen, 4*sizeof(msgLen[0]));
        msgLen[prefixData+1] = '\0';
        if(prefixData == 0)
                return "";
        if(prefixData != 4 || prefixData == -1)
            continue;

        int messageSize = std::stoi(msgLen);

        int data = read(this->sockets[this->mode], buf, messageSize*sizeof(buf[0]));
        buf[data] = '\0';
        LOG_DEBUG("[SocketPair::Receive] We got a message with size: %d and data %s", messageSize, buf);
        return std::string(buf);
    }while(true);

}

void BTruckers::Server::Core::SocketPair::Send(std::string data)
{
    std::string msgLen = std::to_string(data.length());
    msgLen.insert(0, 4-msgLen.length(),'0');
    std::string msg = msgLen+data;
    LOG_DEBUG("[SocketPair::Send] Sending the data...'%s'", msg.c_str());

    write(this->sockets[this->mode], msg.c_str(), msg.length()*sizeof(msg[0]));

}

BTruckers::Server::Core::SocketPair::~SocketPair()
{
    close(this->sockets[this->parentSocket]);
    close(this->sockets[this->childSocket]);
}
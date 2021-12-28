#include "Client.h"

BTruckers::Client::Communcation::Communcation(const char* ip, int port)
{
    LOG_INFO("Trying to connect to server...");
    if(!this->InitiateConnection(ip, port))
    {
        LOG_ERROR("Couldn't connect to the server. Try again.");
        exit(1);
    }
    LOG_INFO("Connection with server was successful.");
}

bool BTruckers::Client::Communcation::InitiateConnection(const char* ip, int port)
{
    BTruckers::Shared::Utils::CheckResponse(this->clientSocket = socket(AF_INET, SOCK_STREAM, 0),"Failed to create a socket");
    struct sockaddr_in serverSocket;

    serverSocket.sin_family = AF_INET;
    serverSocket.sin_addr.s_addr = inet_addr(ip);
    serverSocket.sin_port = port;

    LOG_DEBUG("Initiating connection now.");
    BTruckers::Shared::Utils::CheckResponse(connect(this->clientSocket, (struct sockaddr*)&serverSocket, sizeof(struct sockaddr)),"Failed to initiate connection with the server.");

    return true;
}

std::string BTruckers::Client::Communcation::ReadFromCLI()
{
    char* message = new char[MAXIMUM_READ_BUFFER+1];
    memset(message, 0, MAXIMUM_READ_BUFFER+1);
    
    printf("[>] Enter a command: ");
    fflush(stdout);
    read(0, message, MAXIMUM_READ_BUFFER);
    message[strlen(message)-1] = 0;

    return std::string(message);
}

int BTruckers::Client::Communcation::GetClientSocket()
{
    return this->clientSocket;
}
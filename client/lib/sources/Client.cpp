#include "Client.h"

BTrucks::Client::Client(const char* ip, int port)
{
    Logger::Info("Trying to connect to server...");
    if(!this->InitiateConnection(ip, port))
    {
        Logger::Error("Couldn't connect to the server. Try again.");
        exit(1);
    }
    Logger::Info("Connection with server was successful.");
}

bool BTrucks::Client::InitiateConnection(const char* ip, int port)
{
    BTrucks::Utils::CheckResponse(this->clientSocket = socket(AF_INET, SOCK_STREAM, 0),"Failed to create a socket");
    struct sockaddr_in serverSocket;

    serverSocket.sin_family = AF_INET;
    serverSocket.sin_addr.s_addr = inet_addr(ip);
    serverSocket.sin_port = port;

    Logger::Debug("Initiating connection now.");
    BTrucks::Utils::CheckResponse(connect(this->clientSocket, (struct sockaddr*)&serverSocket, sizeof(struct sockaddr)),"Failed to initiate connection with the server.");

    return true;
}

std::string BTrucks::Client::ReadFromCLI()
{
    char* message = new char[MAXIMUM_READ_BUFFER+1];
    memset(message, 0, MAXIMUM_READ_BUFFER+1);
    
    printf("[>] Enter a command: ");
    fflush(stdout);
    read(0, message, MAXIMUM_READ_BUFFER);
    message[strlen(message)-1] = 0;

    return std::string(message);
}


bool BTrucks::Client::SendMessage(std::string message)
{
    if(message == "")
        return false;
    const char* cstrMsg = message.c_str();
    printf("MEssage to be sent: '%s'\n", cstrMsg);
    BTrucks::Utils::CheckResponse(write(this->clientSocket, cstrMsg, message.length()*sizeof(char)), "Failed to send the message");
    return true;
}

#include "Server.h"


BTruckers::Server::Core::Server::Server(int PORT, int BACKLOG)
{
    LOG_INFO("Initiating socket connection");
    if(!this->Setup(PORT, BACKLOG))
    {
        LOG_CRITICAL("Failed to start the server. Exiting");
        exit(-1);
    }
    LOG_INFO("Started listening on port %d!",PORT);
}
BTruckers::Server::Core::Server::~Server()
{

}

int BTruckers::Server::Core::Server::InitiateConnectionWithClient()
{
    struct sockaddr_in client;
    int clientSocket;
    socklen_t clientSize = sizeof(sockaddr_in);

    memset(&client, 0, sizeof(client));
    
    
    BTruckers::Server::Utils::CheckResponse(clientSocket = accept(this->serverSocket, (struct sockaddr*) &client,(socklen_t*) &clientSocket), "Failed to accept client connection");

    return clientSocket;
}

bool BTruckers::Server::Core::Server::Setup(int PORT, int BACKLOG)
{
    BTruckers::Server::Utils::CheckResponse((this->serverSocket = socket(AF_INET, SOCK_STREAM, 0)), "Failed to create the server socket");
    LOG_DEBUG("Successfully created the socket");
    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = PORT;

    //binding the port and starting to listen on it.
    BTruckers::Server::Utils::CheckResponse(bind(this->serverSocket,(struct sockaddr*) &server, sizeof(server)), "Port is already used. Failed to bind.");
    BTruckers::Server::Utils::CheckResponse(listen(this->serverSocket, BACKLOG), "Failed to listen on specified port.");
    
    return true;
}


std::string BTruckers::Server::Core::Server::ReadMessage(int clientSocket)
{
    char lengthChar[5];
    size_t bytesRead;
    bytesRead = read(clientSocket, lengthChar, 4*sizeof(char));
    lengthChar[4] = 0;

    size_t msgLen = std::atoi(lengthChar);

    char *actualMessage = new char[msgLen+1];
    bytesRead = read(clientSocket, actualMessage, msgLen*sizeof(char));
    actualMessage[msgLen]=0;
    return std::string(actualMessage);
}

int& BTruckers::Server::Core::Server::getServerSocket()
{
    return this->serverSocket;
}

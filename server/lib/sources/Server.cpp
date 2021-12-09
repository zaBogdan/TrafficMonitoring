#include "Server.h"

BTrucks::Server::Server(int PORT, int BACKLOG)
{
    Logger::Debug("Initiating socket connection");
    if(!this->Setup(PORT, BACKLOG))
    {
        Logger::Critical("Failed to start the server. Exiting");
        exit(-1);
    }
    Logger::Info("Started listening on port " + std::to_string(PORT));
}
BTrucks::Server::~Server()
{

}

int BTrucks::Server::InitiateConnectionWithClient()
{
    struct sockaddr_in client;
    int clientSocket;
    socklen_t clientSize = sizeof(sockaddr_in);

    memset(&client, 0, sizeof(client));
    
    BTrucks::Utils::CheckResponse(clientSocket = accept(this->serverSocket, (struct sockaddr*) &client,(socklen_t*) &clientSocket), "Failed to accept client connection");

    return clientSocket;
}

bool BTrucks::Server::Setup(int PORT, int BACKLOG)
{
    BTrucks::Utils::CheckResponse((this->serverSocket = socket(AF_INET, SOCK_STREAM, 0)), "Failed to create the server socket");
    Logger::Debug("Successfully created the socket");
    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = PORT;

    BTrucks::Utils::CheckResponse(bind(this->serverSocket,(struct sockaddr*) &server, sizeof(server)), "Port is already used. Failed to bind.");
    BTrucks::Utils::CheckResponse(listen(this->serverSocket, BACKLOG), "Failed to listen on specified port.");
    return true;
}

int& BTrucks::Server::getServerSocket()
{
    return this->serverSocket;
}

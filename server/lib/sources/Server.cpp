#include "../includes/Server.h"

BTrucks::Server::Server()
{
    Logger::Debug("Initiating socket connection");
    if(!this->Setup())
    {
        Logger::Critical("Failed to start the server. Exiting");
        exit(-1);
    }
    Logger::Info("Started listening on port " + std::to_string(BTrucks::runningPort));
}
BTrucks::Server::~Server()
{

}

int BTrucks::Server::InitiateConnection()
{
    struct sockaddr_in client;
    int clientSocket;
    socklen_t clientSize = sizeof(sockaddr_in);

    memset(&client, 0, sizeof(client));

    this->CheckResponse(clientSocket = accept(this->serverSocket, (struct sockaddr*) &client,(socklen_t*) &clientSocket), "Failed to accept client connection");

    return clientSocket;
}

bool BTrucks::Server::Setup()
{
    this->CheckResponse((this->serverSocket = socket(AF_INET, SOCK_STREAM, 0)), "Failed to create the server socket");
    Logger::Debug("Successfully created the socket");
    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = BTrucks::runningPort;

    this->CheckResponse(bind(this->serverSocket,(struct sockaddr*) &server, sizeof(server)), "Port is already used. Failed to bind.");
    this->CheckResponse(listen(this->serverSocket, BTrucks::backLog), "Failed to listen on specified port.");
    return true;
}

int BTrucks::Server::CheckResponse(int result, const char *errorMessage)
{
    if(result == this->ERROR_SOCKET)
    {
        Logger::Error(errorMessage);
        exit(result);
    }
    return result;
}

std::string BTrucks::Server::GetSocketMessage(int clientSocket)
{
    return "";
}

bool BTrucks::Server::SendMessage(int clientSocket)
{
    return true;
}

int& BTrucks::Server::getServerSocket()
{
    return this->serverSocket;
}

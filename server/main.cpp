#include "BTRCommon.h"
#include "BTrucksShared.h"
#include "Server.h"
#include "Logger.h"
#include "SocketOperations.h"
#include "Tokens.h"

int main()
{
    BTrucks::Server server;
    SocketOperations *communcation = SocketOperations::GetInstance();
    
    if(DEBUG_MODE == true)
    {
        Logger::SetLoggingLevel(BTrucksShared::Utils::LoggingLevel::DEBUG);
        Logger::Debug("Application is now running in verbose mode...");
    }
    Logger::Info("Attempting to start the server");
    communcation->GetMessage(server.getServerSocket());
    BTrucks::Tokens token;

    Logger::Debug("You have here a token: "+ token.Generate());
    while(true)
    {
        Logger::Info("Waiting for new connections...");
        int newSocket = server.InitiateConnection();

        // std::string message = server.GetSocketMessage(newSocket);
    }

    return 0;
}
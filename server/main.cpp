#include "lib/includes/BTrucks.h"
#include "../shared/lib/includes/BTrucksShared.h"
#include "lib/includes/Server.h"
#include "../shared/lib/includes/Logger.h"
#include "../shared/lib/includes/SocketOperations.h"
#define DEBUG_MODE true

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

    while(true)
    {
        Logger::Info("Waiting for new connections...");
        int newSocket = server.InitiateConnection();

        // std::string message = server.GetSocketMessage(newSocket);
    }

    return 0;
}
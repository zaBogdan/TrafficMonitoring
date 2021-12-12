#include "BTRCommon.h"
#include "BTRShared.h"
#include "Server.h"
#include "Logger.h"
#include "Tokens.h"

int main()
{
    BTrucks::Server server;
    // SocketOperations *communcation = SocketOperations::GetInstance();
    
    if(DEBUG_MODE == true)
    {
        Logger::SetLoggingLevel(BTRShared::Utils::LoggingLevel::DEBUG);
        Logger::Debug("Application is now running in verbose mode...");
    }
    Logger::Info("Attempting to start the server");

    while(true)
    {
        Logger::Info("Waiting for new connections...");
        int newSocket = server.InitiateConnectionWithClient();

        // std::string message = server.GetSocketMessage(newSocket);
    }

    return 0;
}
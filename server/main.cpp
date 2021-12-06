#include "lib/includes/BTrucks.h"
#include "lib/includes/Logger.h"
#include "lib/includes/Server.h"
#define DEBUG_MODE true

int main()
{
    if(DEBUG_MODE == true)
    {
        Logger::SetLoggingLevel(BTrucks::Utils::LoggingLevel::DEBUG);
        Logger::Debug("Application is now running in verbose mode...");
    }
    Logger::Info("Attempting to start the server");
    BTrucks::Server server;

    while(true)
    {
        Logger::Info("Waiting for new connections...");
        int newSocket = server.InitiateConnection();

    //     std::string message = server.GetSocketMessage(newSocket);
    }

    return 0;
}
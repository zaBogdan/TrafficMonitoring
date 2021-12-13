#include "BTRCommon.h"
#include "BTRShared.h"
#include "Server.h"
#include "Logger.h"
#include "Message.h"

int main()
{
    BTrucks::Server server;
    fd_set currentSockets, readySockets;
    FD_ZERO(&currentSockets);
    FD_SET(server.getServerSocket(), &currentSockets);
    
    if(DEBUG_MODE == true)
    {
        Logger::SetLoggingLevel(BTRShared::Utils::LoggingLevel::DEBUG);
        Logger::Debug("Application is now running in verbose mode...");
    }
    Logger::Info("Attempting to start the server");


    while(true)
    {
        readySockets = currentSockets;

        if(select(FD_SETSIZE, &readySockets, NULL, NULL, NULL) < 0)
        {
            Logger::Info("Failed for some reason.");
            exit(0);
        }
        Logger::Info("Found some data to be reading onto.");

        for(int i=0;i<FD_SETSIZE;i++)
        {
            if(FD_ISSET(i, &readySockets))
            {
                if(i == server.getServerSocket())
                {
                    //handling new connection
                    int newSocket = server.InitiateConnectionWithClient();
                    FD_SET(newSocket, &currentSockets);
                }else{
                    //starting to read
                    printf("Starting to read from old connection...");
                    std::string recvMessage = server.ReadMessage(i);
                    if(recvMessage == "")
                    {
                        FD_CLR(i, &currentSockets);
                    }
                }
            }
        }
    }

    return 0;
}
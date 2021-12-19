#include "BTRCommon.h"
#include "BTRShared.h"
#include "Server.h"
#include "Logger.h"
#include "Message.h"
#include "Command.h"
#include <signal.h>

int main()
{
    fd_set currentSockets, readySockets;
    if(DEBUG_MODE == true)
    {
        Logger::SetLoggingLevel(BTRShared::Utils::LoggingLevel::DEBUG);
        LOG_DEBUG("Application is now running in verbose mode...");
    }
    LOG_INFO("Attempting to start the server");
    BTrucks::Server server;

    //initializing the multiplexing
    FD_ZERO(&currentSockets);
    FD_SET(server.getServerSocket(), &currentSockets);

    while(true)
    {
        //to be improved
        readySockets = currentSockets;
        LOG_DEBUG("Waiting for select to find something.");
        BTrucks::Utils::CheckResponse(select(FD_SETSIZE, &readySockets, NULL, NULL, NULL), "Select failed.");

        LOG_INFO("Select returned. Going to check the connections");
        for(int i=0;i<FD_SETSIZE;i++)
        {
            if(FD_ISSET(i, &readySockets))
            {
                if(i == server.getServerSocket())
                {
                    LOG_INFO("Found a new connection.");
                    //handling new connection
                    int newSocket = server.InitiateConnectionWithClient();
                    FD_SET(newSocket, &currentSockets);
                }else{
                    //starting to read
                    LOG_DEBUG("Starting to read from old connection...");

                    // printf("Starting to read from old connection...");
                    std::string recvMessage = server.ReadMessage(i);
                    if(recvMessage == "")
                    {
                        LOG_INFO("Connection killed.");
                        close(i);
                        FD_CLR(i, &currentSockets);
                    }else{
                        //each request has its own process until it finishes. 
                        LOG_INFO("Spawning a new process.");
                        pid_t newRequestProcess = fork();
                        BTrucks::Utils::CheckResponse(newRequestProcess, "Failed to handle a new request. Fork failure...");
                        if(newRequestProcess==0)
                        {
                            printf("[Proccess] Started working with on pid %d with parent %d.\n", getpid(), getppid());
                            std::string response = BTrucks::CommandHandler::Handle(recvMessage);
                            printf("[Proccess] Task finished with response '%s'. Killing process %d...\n",response.c_str(), getpid());
                            kill(getpid(),SIGKILL);
                        }else{
                            printf("[zaBogdan] Returned to parent with pid %d\n", getpid());
                        }
                    }
                }
            }
        }
        LOG_INFO("Finished the handler. ");
    }

    return 0;
}
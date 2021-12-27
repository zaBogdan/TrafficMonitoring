#include "BTRCommon.h"
#include "BTRShared.h"
#include "Server.h"
#include "Logger.h"
#include "protocols/TCP.h"
#include "CPV.h"
#include "DBHandler.h"
#include "SocketPair.h"
#include <signal.h>
#include <pthread.h>


void* broadcasterRoutine(void *arg)
{
    // fd_set activeConnections = *((fd_set*) arg);
    // LOG_INFO("[ BROADCASTER ] The thread has been successfully initialized.");
    // while(true)
    // {
    //     LOG_DEBUG("[ BROADCASTER ] Starting to broadcast information to all clients that have selected this.");


    //     //this thread will have activity each minute
    //     sleep(60);
    // }

    // LOG_INFO("[ BROADCASTER ] Now exiting...");
    // fflush(stdout);	 

    return nullptr;
}

int main()
{
    signal(SIGINT, BTruckers::Server::Utils::SignalHandler);
    if(DEBUG_MODE == true)
    {
        
        Logger::SetLoggingLevel(BTruckers::Shared::Enums::LoggingLevel::DEBUG);
        LOG_DEBUG("Application is now running in verbose mode...");
    }

    //declarations...
    BTruckers::Server::Core::DBHandler db;

    //getting a copy for the connections.
    fd_set currentSockets, readySockets;

    LOG_INFO("Attempting to start the server");
    //the server instance
    BTruckers::Server::Core::Server server;
    //the handler for the messages
    BTruckers::Server::Core::CPV cpv;

    //initializing the multiplexing
    FD_ZERO(&currentSockets);
    FD_SET(server.getServerSocket(), &currentSockets);



    while(true)
    {
        //copy for select.
        readySockets = currentSockets;
        LOG_DEBUG("Waiting for socket activity...");
        BTruckers::Server::Utils::CheckResponse(select(FD_SETSIZE, &readySockets, NULL, NULL, NULL), "Select failed.");
        for(int clientIDX=0;clientIDX<FD_SETSIZE;clientIDX++)
        {
            //if the socket isn't ready we continue
            if(!FD_ISSET(clientIDX, &readySockets))
                continue;
            
            LOG_DEBUG("Socket with id '%d' is ready. Now checking what to do.", clientIDX);
            if(clientIDX == server.getServerSocket())
            {
                //this is the server code.
                LOG_INFO("Server socket has received a new connection.");
                int newClient = server.InitiateConnectionWithClient();
                FD_SET(newClient, &currentSockets);
                //we need to skip until the end.
                continue;
            }
            BTruckers::Server::Core::SocketPair interComm;

            //if the socket wasn't the one assigned to the server we will create a new process
            pid_t requestProcess = fork();
            BTruckers::Server::Utils::CheckResponse(requestProcess, "Failed to create a process for incoming request.");
            LOG_DEBUG("Spawned process %d for clientIDX %d", requestProcess, clientIDX);
            if(requestProcess == 0)
            {
                interComm.SelectMode(CHILD_MODE);
                std::string clientMsg = interComm.Receive();
                int currentClient = std::stoi(clientMsg);
                //here we will handle the process data.
                LOG_DEBUG("[ PROCESS %d ] Starting to handle the request for client '%d'.", getpid(), currentClient);

                std::string message = BTruckers::Shared::Protocols::TCP::Receive(currentClient);
                if(message == "")
                {
                    FD_CLR(currentClient, &currentSockets);
                    shutdown(currentClient, 2);
                    close(currentClient);
                }

                // BTruckers::Shared::Structures::Message request = cpv.Parse(message);
                // std::string response = BTruckers::Server::Commands::Handler(request);

                LOG_DEBUG("[ PROCESS %d ] The response is: %s", getpid(), message.c_str());

                LOG_DEBUG("[ PROCESS %d ] Finished handling the request. Exiting...", getpid());
                // killing the process now
                if(kill(getpid(),SIGTERM)==-1)
                {
                    LOG_CRITICAL("FAILED TO KILL MYSELF!!!");
                }
                fflush(stderr);
                exit(0);
            }else{
                interComm.SelectMode(PARENT_MODE);
                interComm.Send(std::to_string(clientIDX));
                LOG_INFO("Finished to handle the request for client '%d'", clientIDX);
            }

        }
    }

    //waiting for the thread to finish (just to be safe nothing breaks.)
    LOG_INFO("Waiting for all threads to finish");
    // pthread_join(thread1, &threadResults);
    LOG_INFO("The server is now shutting down...");
    return 0;
}

/**

each client should be stored in something like:
1. clientSocket (int)
2. clientProcess (pid_t) (this might be deprecated)
3. emptyMessages (unsigned int)
4. uuid (string) - "" if is not logged in, otherwise the uuid
5. message (string)




 * 
 */
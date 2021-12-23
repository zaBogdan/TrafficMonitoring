#include "BTRCommon.h"
#include "BTRShared.h"
#include "Server.h"
#include "Logger.h"
#include "protocols/TCP.h"
#include "CPV.h"
#include "DBHandler.h"
#include "models/Users.h"
#include <signal.h>

#include <iostream>

int main()
{
    if(DEBUG_MODE == true)
    {
        
        Logger::SetLoggingLevel(BTruckers::Shared::Enums::LoggingLevel::DEBUG);
        LOG_DEBUG("Application is now running in verbose mode...");
    }
    BTruckers::Server::Core::DBHandler db;
    
    BTruckers::Server::Models::Users user;
    user.GetUserByUsername("gigimuschi");
    user.lastname = "Hellomania";
    user.company = "Doodler";
    user.Update();
    user.GetUserByUUID();

    return 0;
    // fd_set currentSockets, readySockets;

    // LOG_INFO("Attempting to start the server");
    // BTruckers::Server::Core::Server server;
    // BTruckers::Server::Core::CPV cpv;

    // //initializing the multiplexing
    // FD_ZERO(&currentSockets);
    // FD_SET(server.getServerSocket(), &currentSockets);

    // while(true)
    // {
    //     //to be improved
    //     readySockets = currentSockets;
    //     LOG_DEBUG("Waiting for select to find something.");
    //     BTruckers::Server::Utils::CheckResponse(select(FD_SETSIZE, &readySockets, NULL, NULL, NULL), "Select failed.");
        
    //     LOG_INFO("Select returned. Going to check the connections");
    //     for(int i=0;i<FD_SETSIZE;i++)
    //     {
    //         if(FD_ISSET(i, &readySockets))
    //         {
    //             if(i == server.getServerSocket())
    //             {
    //                 LOG_INFO("Found a new connection.");
    //                 //handling new connection
    //                 int newSocket = server.InitiateConnectionWithClient();
    //                 FD_SET(newSocket, &currentSockets);
    //             }else{
    //                 //starting to read
    //                 LOG_DEBUG("Starting to read from old connection...");

    //                 // printf("Starting to read from old connection...");
    //                 // std::string recvMessage = server.ReadMessage(i);
    //                 std::string recvMessage = BTruckers::Shared::Protocols::TCP::Receive(i); 
    //                 if(recvMessage == "")
    //                 {
    //                     LOG_INFO("Connection killed.");
    //                     close(i);
    //                     FD_CLR(i, &currentSockets);
    //                 }else{
    //                     //each request has its own process until it finishes. 
    //                     LOG_INFO("Spawning a new process.");
    //                     pid_t newRequestProcess = fork();
    //                     BTruckers::Server::Utils::CheckResponse(newRequestProcess, "Failed to handle a new request. Fork failure...");
    //                     if(newRequestProcess==0)
    //                     {
    //                         printf("[Proccess] Started working with on pid %d with parent %d.\n", getpid(), getppid());

    //                         BTruckers::Shared::Structures::Message request = cpv.Parse(recvMessage);
    //                         std::string response = BTruckers::Server::Commands::Handler(request);
    //                         printf("[Proccess] Task finished with response '%s'. Killing process %d...\n",response.c_str(), getpid());
    //                         kill(getpid(),SIGKILL);
    //                     }else{
    //                         printf("[zaBogdan] Returned to parent with pid %d\n", getpid());
    //                     }
    //                 }
    //             }
    //         }
    //     }
    //     LOG_INFO("Finished the handler. ");
    // }

    // return 0;
}
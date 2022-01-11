#include <stdlib.h>
#include "BTRClient.h"
#include "BTRShared.h"
#include "Client.h"
#include "CPV.h"
#include "protocols/TCP.h"
#include <ctime>
#include <iostream>

void printHelp(char* toolName)
{
    printf("BTruckers Client\n");
    printf("Copyright (c) Bogdan Zavadovschi. All rights reserved.\n");
    printf("Usage: %s [serverIP/DNS] [port]\n", toolName);
}

int main(int argc, char *argv[])
{
    if(argc<3)
    {
        printHelp(argv[0]);
        return 1;
    }

    if(DEBUG_MODE == true)
    {
        Logger::SetLoggingLevel(BTruckers::Shared::Enums::LoggingLevel::DEBUG);
        LOG_DEBUG("Application is now running in verbose mode...");
    }

    LOG_DEBUG("Starting to initiate connection to the server");

    // client trying to connect to the server
    BTruckers::Client::Core::Communcation client(argv[1], atoi(argv[2]));
    BTruckers::Client::Core::CPV cpv;

    fd_set readySockets, copySockets;
    FD_ZERO(&readySockets);
    FD_SET(fileno(stdin), &readySockets);
    FD_SET(client.GetClientSocket(), &readySockets);
    uint8_t FDSetSize = std::max(fileno(stdin), client.GetClientSocket())+1;

    while(true)
    {
        bool stillRunning = true;
        copySockets = readySockets;
        printf("[>] Enter a command: ");
        fflush(stdout);
        int ret = select(FDSetSize, &copySockets, NULL, NULL, NULL);
        if(ret < 0){
            LOG_ERROR("Select failed... uninting the client.");
            break;
        }

        for(int idx = 0; idx < FDSetSize; ++idx)
        {
            if(!FD_ISSET(idx, &copySockets))
                continue;
            
            if(idx == fileno(stdin))
            {
                //if we are reading some user input we will send it to another thread
                LOG_DEBUG("Reading user input");
                std::string requestCommand = client.ReadFromCLI();

                LOG_DEBUG("[ %d ] Request is: %s",idx, requestCommand.c_str());

                continue;
            }

            LOG_DEBUG("[ %d ] Reading from server socket.", idx);
            std::string socketResponse = BTruckers::Shared::Protocols::TCP::Receive(idx);
            if(socketResponse == "")
            {
                stillRunning = false;
            }
            LOG_DEBUG("[ %d ] Response is: %s",idx, socketResponse.c_str());


        }

        //check if we lost server connection
        if(!stillRunning) break;


        //if flag set, write the speed to the server

        //schedule 1 min alarm to send data.
    }

    LOG_INFO("Uninitializing the client...");
    // std::vector<std::string> requests = {"login zaBogdan:P@ssw0rd2", "incident 20"};

    // for(auto request : requests)
    // {
    //     LOG_DEBUG("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=")
    //     LOG_DEBUG("Command is: %s", request.c_str());
    //     std::string requestCommand = request;

    //     BTruckers::Shared::Structures::Message msg = cpv.Craft(requestCommand);
    //     requestCommand = BTruckers::Client::Commands::HandleResponse(msg);

    //     if(requestCommand == "")
    //         continue;
        
    //     BTruckers::Shared::Protocols::TCP::Send(client.GetClientSocket(), requestCommand);
        
        // std::string socketResponse = BTruckers::Shared::Protocols::TCP::Receive(client.GetClientSocket());
    //     msg = cpv.Parse(socketResponse);

    //     std::string response = BTruckers::Client::Commands::HandleResponse(msg, false);
    //     printf("[<] Response: %s\n", response.c_str());
    // }

    // do{
        // std::string requestCommand = client.ReadFromCLI();
    //     // std::string requestCommand = "login zaBogdan:P@ssw0rd2";

    //     BTruckers::Shared::Structures::Message msg = cpv.Craft(requestCommand);
    //     requestCommand = BTruckers::Client::Commands::HandleResponse(msg);

    //     if(requestCommand == "")
    //         continue;
        
    //     BTruckers::Shared::Protocols::TCP::Send(client.GetClientSocket(), requestCommand);
        
    //     std::string socketResponse = BTruckers::Shared::Protocols::TCP::Receive(client.GetClientSocket());
    //     msg = cpv.Parse(socketResponse);

    //     std::string response = BTruckers::Client::Commands::HandleResponse(msg, false);
    //     printf("[<] Response: %s\n", response.c_str());
    //     // break;
    // }while(true);
    return 0;
}

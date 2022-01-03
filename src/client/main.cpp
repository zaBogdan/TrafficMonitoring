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
    printf("BTruckers::Client Client\n");
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


    do{
        std::string requestCommand = client.ReadFromCLI();
        // std::string requestCommand = "login zaBogdan:P@ssw0rd2";

        BTruckers::Shared::Structures::Message msg = cpv.Craft(requestCommand);
        requestCommand = BTruckers::Client::Commands::HandleResponse(msg);

        if(requestCommand == "")
            continue;
        
        BTruckers::Shared::Protocols::TCP::Send(client.GetClientSocket(), requestCommand);
        
        std::string socketResponse = BTruckers::Shared::Protocols::TCP::Receive(client.GetClientSocket());
        msg = cpv.Parse(socketResponse);

        std::string response = BTruckers::Client::Commands::HandleResponse(msg);
        printf("[<] Response: %s\n", response.c_str());
        // break;
    }while(true);


    return 0;
}

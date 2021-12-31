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

    //client trying to connect to the server
    BTruckers::Client::Core::Communcation client(argv[1], atoi(argv[2]));
    BTruckers::Client::Core::CPV cpv;


    do{
        // std::string msg = client.ReadFromCLI();
        std::string msg = "login zaBogdan:P@ssw0rd2";
        LOG_DEBUG("The message that we read was %s",msg.c_str());
        msg = cpv.Craft(msg);
        BTruckers::Shared::Protocols::TCP::Send(client.GetClientSocket(), msg);
        if(msg == "")
            continue;
        std::string response = BTruckers::Shared::Protocols::TCP::Receive(client.GetClientSocket());
        LOG_DEBUG("Response is: %s",response.c_str());
        break;
    }while(true);
//do an internal state management for this
// |SetTokens:d{sidentifier:39A26E12AE3765A5,svalidator:9F5DA3705AD54E29}
    return 0;
}
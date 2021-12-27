#include <stdlib.h>
#include "BTRClient.h"
#include "BTRShared.h"
// #include "Message.h"
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
    if(argc<2)
    {
        printHelp(argv[0]);
        return 1;
    }
    if(DEBUG_MODE == true)
    {
        Logger::SetLoggingLevel(BTruckers::Shared::Enums::LoggingLevel::DEBUG);
        LOG_DEBUG("Application is now running in verbose mode...");
    }
    srand (time(NULL));

    LOG_DEBUG("Starting to initiate connection to the server");

    //client trying to connect to the server
    BTruckers::Client::Communcation client(argv[1], atoi(argv[2]));
    BTruckers::Client::Core::CPV cpv;

    std::string conn = std::to_string(atoi(argv[3]));

    do{
        // std::string msg = client.ReadFromCLI();
        std::string msg = "login zaBogdan:P@ssw0rd1"+conn;
        LOG_DEBUG("The message that we read was %s",msg.c_str());
        msg = cpv.Craft(msg);
        BTruckers::Shared::Protocols::TCP::Send(client.GetClientSocket(), msg);
        break;
    }while(true);

    return 0;
}
/*
I should have two threads, or processes (to be decided...?)

*/
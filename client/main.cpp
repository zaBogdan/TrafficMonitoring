#include <stdlib.h>
#include "BTRClient.h"
#include "BTrucksShared.h"
#include "Client.h"

void printHelp(char* toolName)
{
    printf("BTRucks Client\n");
    printf("Copyright (c) Bogdan Zavadovschi. All right reserved.\n");
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
        Logger::SetLoggingLevel(BTrucksShared::Utils::LoggingLevel::DEBUG);
        Logger::Debug("Application is now running in verbose mode...");
    }
    Logger::Debug("Starting to initiate connection to the server");
    //client trying to connect to the server∆
    BTrucks::Client client(argv[1], atoi(argv[2]));

    do{
        char* msg = client.ReadFromCLI();
        Logger::Debug("The message that we read was: "+std::string(msg));
        //SocketOperation.formatMessage(msg); //i really should rename this class!
        //client.SendMessage(msg);
    }while(true);

    return 0;
}
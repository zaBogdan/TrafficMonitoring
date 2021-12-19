#include <stdlib.h>
#include "BTRClient.h"
#include "BTRShared.h"
#include "Message.h"
#include "Client.h"
#include "Command.h"

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

    LOG_DEBUG("Starting to initiate connection to the server");

    //client trying to connect to the server
    BTruckers::Client::Communcation client(argv[1], atoi(argv[2]));

    do{
        // std::string msg = client.ReadFromCLI();
        std::string msg = "login zaBogdan:P@ssw0rd1";
        LOG_DEBUG("The message that we read was %s",msg.c_str());
        msg = BTruckers::Client::Handler::Create(msg);
        msg = Message::Format(msg);
        LOG_DEBUG("Final message is: '%s'", msg.c_str());
        client.SendMessage(msg);
        // sleep(10000000);
        break;
    }while(true);

    return 0;
}
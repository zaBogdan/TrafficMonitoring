#include <stdlib.h>
#include "BTRClient.h"
#include "BTRShared.h"
#include "Message.h"
#include "Client.h"
#include "Command.h"

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
        Logger::SetLoggingLevel(BTRShared::Utils::LoggingLevel::DEBUG);
        Logger::Debug("Application is now running in verbose mode...");
    }

    Logger::Debug("Starting to initiate connection to the server");
    //client trying to connect to the server
    // BTrucks::Client client(argv[1], atoi(argv[2]));
    std::string formatedMsg = BTrucks::CommandHandler::Evaluate("Response zaBogdan:P@ssw0rd");

    printf("Formated messsage is: %s\n", formatedMsg.c_str());
    std::string message = Message::Format(formatedMsg);
    printf("Message to be sent to server is: '%s'\n", message.c_str());
    // do{
    //     // std::string msg = client.ReadFromCLI();
    //     // Logger::Debug("The message that we read was: "+std::string(msg));
    //     // msg = Message::Format(msg);
    //     // // Logger::Debug("Final message is: '"+msg+"'");
    //     //client.SendMessage(msg);
    // }while(true);

    return 0;
}
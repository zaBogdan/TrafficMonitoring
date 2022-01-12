#include <stdlib.h>
#include "BTRClient.h"
#include "BTRShared.h"
#include "sensors/SpeedSensor.h"
#include "sensors/GPSSensor.h"
#include "Client.h"
#include "CPV.h"
#include "protocols/TCP.h"
#include <ctime>
#include <iostream>
pthread_mutex_t globalMutexLock;
const int stdinId = fileno(stdin);
volatile sig_atomic_t sendMetrics = false;

void handleAlarm( int sig ) {
    sig = sig;
    sendMetrics = true;
}

bool SendMessageToServer(std::string msg, BTruckers::Client::Core::Communcation* client, BTruckers::Client::Core::CPV* cpv)
{
    if(msg == "")
        return false;
    BTruckers::Shared::Structures::Message pMsg = cpv->Craft(msg);
    std::string requestMsg = BTruckers::Client::Commands::HandleResponse(pMsg);
    if(requestMsg == "")
        return false;
    return BTruckers::Shared::Protocols::TCP::Send(client->GetClientSocket(), requestMsg);
}

void printHelp(char* toolName)
{
    printf("BTruckers Client\n");
    printf("Copyright (c) Bogdan Zavadovschi. All rights reserved.\n");
    printf("Usage: %s [serverIP/DNS] [port]\n", toolName);
}

int main(int argc, char *argv[])
{
    signal(SIGALRM, handleAlarm);
    if(argc<3)
    {
        printHelp(argv[0]);
        return 1;
    }

    // if(DEBUG_MODE == true)
    // {
    //     Logger::SetLoggingLevel(BTruckers::Shared::Enums::LoggingLevel::DEBUG);
    //     LOG_DEBUG("Application is now running in verbose mode...");
    // }

    LOG_DEBUG("Starting to initiate connection to the server");

    // client trying to connect to the server
    BTruckers::Client::Core::Communcation client(argv[1], atoi(argv[2]));
    BTruckers::Client::Core::CPV cpv;
    BTruckers::Shared::Structures::Message msg;
    
    //initializing the sensors
    BTruckers::Client::Sensors::Speed speedSensor;
    BTruckers::Client::Sensors::GPS gpsSensor;

    char sendMessage[60];

    fd_set readySockets, copySockets;
    FD_ZERO(&readySockets);
    FD_SET(stdinId, &readySockets);
    FD_SET(client.GetClientSocket(), &readySockets);
    uint8_t FDSetSize = std::max(stdinId, client.GetClientSocket())+1;

    bool stillRunning = true, alarmFail = false;
    //setting the first alaram in 1 second
    alarm(1);
    while(stillRunning)
    {
        alarmFail = false;
        copySockets = readySockets;
        printf("[>] Enter a command: ");
        fflush(stdout);
        int ret = select(FDSetSize, &copySockets, NULL, NULL, NULL);
        if(ret < 0){
            if(errno == EINTR)
            {
                LOG_DEBUG("Select failed because of an alarm");
                alarmFail = true;
            }else{
                LOG_ERROR("Select failed with code %d... uninting the client.", ret);
                break;
            }
        }

        for(int idx = 0; idx < FDSetSize && !alarmFail; ++idx)
        {
            if(!FD_ISSET(idx, &copySockets))
                continue;
            
            if(idx == stdinId)
            {
                //if we are reading some user input we will send it to another thread
                LOG_DEBUG("Reading user input");
                std::string requestCommand = client.ReadFromCLI();

                if(!SendMessageToServer(requestCommand, &client, &cpv))
                {
                    LOG_WARNING("Failed to send message '%s' to the server", requestCommand.c_str());
                }
                continue;
            }
            //if we don't have anything to read, the server broadcasted to us. 
            printf("\n");
            LOG_DEBUG("[ %d ] Reading from server socket.", idx);
            std::string socketResponse = BTruckers::Shared::Protocols::TCP::Receive(idx);
            
            //check if we lost server connection
            if(socketResponse == "")
            {
                LOG_WARNING("Lost connection with server... warm shutdown started.");
                stillRunning = false;
            }
            
            msg = cpv.Parse(socketResponse);

            std::string response = BTruckers::Client::Commands::HandleResponse(msg, false);
            printf("[<] Response: %s\n", response.c_str());
        }

        printf("\n");
        //checking alarm trigger
        if(!sendMetrics)
            continue;
        sendMetrics = false;
        
        //alarm logic
        LOG_DEBUG("Received an ALARM signal. Sending the metrics now...");
        speedSensor.Read();
        std::pair<long long, long long> gpsData = gpsSensor.Read();
        //send the data now.
        sprintf(sendMessage, "metrics %d %lld %lld", speedSensor.Read(),gpsData.first, gpsData.second);
        LOG_DEBUG("Message is: %s", sendMessage);
        
        if(!SendMessageToServer(sendMessage, &client, &cpv))
        {
            LOG_WARNING("Failed to send message '%s' to the server", sendMessage);
        }

        //schedule 1 min alarm to send data.
        alarm(20);
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

    //     requestCommand = BTruckers::Client::Commands::HandleResponse(msg);

    //     if(requestCommand == "")
    //         continue;
        
    //     BTruckers::Shared::Protocols::TCP::Send(client.GetClientSocket(), requestCommand);
        
    //     std::string socketResponse = BTruckers::Shared::Protocols::TCP::Receive(client.GetClientSocket());
    //     // break;
    // }while(true);
    return 0;
}

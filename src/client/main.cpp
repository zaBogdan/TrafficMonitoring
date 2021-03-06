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
bool stillRunning = true;

void HandleSignal(int sig)
{
    switch(sig)
    {
        case SIGINT:
        case SIGKILL:
        case SIGTERM:
            stillRunning = false;
            alarm(1);
            LOG_INFO("Warm shutdown procedure started.");
            break;
        default:
            LOG_INFO("Signal not supported yet");
    }
}
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
    if(requestMsg == "Help")
        return true;
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
    signal(SIGINT, HandleSignal);
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

    bool alarmFail = false, firstRun = true;
    //setting the first alaram in 1 second
    alarm(1);
    while(stillRunning)
    {
        alarmFail = false;
        copySockets = readySockets;
        if(!firstRun)
        {
            printf("[>] Enter a command: ");
        }
        firstRun = false;
        fflush(stdout);
        int ret = select(FDSetSize, &copySockets, NULL, NULL, NULL);
        printf("\n");
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
                if(requestCommand == "exit")
                {
                    stillRunning = false;
                    continue;
                }
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
            if(response != BROADCAST_COMMAND)
            {
                printf("[<] Response: %s\n", response.c_str());
            }
        }

        //checking alarm trigger
        if(!sendMetrics)
            continue;
        printf("\n");

        //if we are not authenticated we will not send the metrics
        if(BTruckers::Client::Core::StorageBox::GetItem("identifier") == "")
            continue;
        
        //alarm logic
        LOG_DEBUG("Received an ALARM signal. Sending the metrics now...");
        BTruckers::Shared::Structures::Cords gpsData = gpsSensor.Read();
        //send the data now.
        sprintf(sendMessage, "metrics %d %.6f %.6f", speedSensor.Read(),gpsData.longitute, gpsData.latitude);
        
        if(!SendMessageToServer(sendMessage, &client, &cpv))
        {
            LOG_WARNING("Failed to send message '%s' to the server", sendMessage);
        }

        sendMetrics = false;
        //schedule 1 min alarm to send data.
        alarm(60);
    }

    LOG_INFO("Uniniting the client...");
    BTruckers::Client::Core::StorageBox::DumpToFile();
    return 0;
}

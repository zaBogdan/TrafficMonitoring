#include "BTRCommon.h"
#include "BTRShared.h"
#include "Server.h"
#include "Logger.h"
#include "protocols/TCP.h"
#include "CPV.h"
#include "DBHandler.h"
#include "SocketPair.h"
#include <signal.h>
#include <pthread.h>

struct Thread
{
    int idx = 0;
    int count = 0;
    std::vector<int> sockets;
};


void* threadFunction(void* arg)
{
    Thread* idx = (Thread*) arg;
    while(true)
    {
        LOG_DEBUG("[ THREAD %d ] The count is: %d ----",idx->idx, idx->count);
        for(auto it : idx->sockets)
        {
            LOG_DEBUG("[ THREAD %d ] The socket values are: %d ----",idx->idx, it);
        }
        sleep(5);
    }
    return nullptr;
}

int main()
{
    signal(SIGINT, BTruckers::Server::Utils::SignalHandler);
    if(DEBUG_MODE == true)
    {
        
        Logger::SetLoggingLevel(BTruckers::Shared::Enums::LoggingLevel::DEBUG);
        LOG_DEBUG("Application is now running in verbose mode...");
    }

    BTruckers::Server::Core::DBHandler db;
    BTruckers::Server::Core::Server server;
    BTruckers::Server::Core::CPV cpv;

    Thread* ThreadInformation = new Thread[THREAD_POOL_SIZE];
    pthread_t threadPool[THREAD_POOL_SIZE];

    for(int idx=0;idx<THREAD_POOL_SIZE;idx++)
    {
        ThreadInformation[idx].idx = idx;
        if(pthread_create(&threadPool[idx], nullptr, &threadFunction, (void*) (ThreadInformation+idx))!=0)
        {
            LOG_CRITICAL("Failed to create a thread. Exiting.");
            exit(-1);
        }
    }
    while(true)
    {
        int clientIDX = server.InitiateConnectionWithClient();
        
        //we want to add this client to the least used thread.
        int minValue=100000, correspondingIDXtoMin=0;
        for(int idx=0;idx<THREAD_POOL_SIZE;idx++)
        {
            if(ThreadInformation[idx].count<minValue)
            {
                minValue = ThreadInformation[idx].count;
                correspondingIDXtoMin = idx;
            }
        }
        LOG_DEBUG("New client connection: %d and sending to to thread %d", clientIDX, ThreadInformation[correspondingIDXtoMin].idx);
        ThreadInformation[correspondingIDXtoMin].count++;
        ThreadInformation[correspondingIDXtoMin].sockets.push_back(clientIDX);
        sleep(1);
    }

    return 0;
}
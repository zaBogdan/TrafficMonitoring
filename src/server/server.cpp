#include "BTRCommon.h"
#include "BTRShared.h"
#include "Server.h"
#include "Logger.h"
#include "protocols/TCP.h"
#include "CPV.h"
#include "DBHandler.h"
#include <signal.h>
#include <pthread.h>
pthread_mutex_t mutexArray[THREAD_POOL_SIZE];
BTruckers::Server::Core::CPV cpv;


//this will handle all the connections
void* threadFunction(void* arg)
{
    BTruckers::Server::Structures::Thread* threadData = (BTruckers::Server::Structures::Thread*) arg;
    
    //starting a database connection
    BTruckers::Server::Core::DBHandler db;

    //setting a timeout for processing new clients
    struct timeval tv;
    //this will slow a bit the connection but it's a must...
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    
    //initializing the multiplexing
    fd_set readySockets;
    pthread_mutex_lock(&mutexArray[threadData->idx]);
    FD_ZERO(&threadData->currentSockets);
    pthread_mutex_unlock(&mutexArray[threadData->idx]);

    //here i don t have to include the server socket because it will be managed 
    //on the main thread(which will only accept and fwd to a thread from the poll)
    fflush(stdout);
    LOG_DEBUG("[ THREAD %d ] I'm initialized now.", threadData->idx);
   
    while(true)
    {
        //copy for select.
        pthread_mutex_lock(&mutexArray[threadData->idx]);
        readySockets = threadData->currentSockets;
        pthread_mutex_unlock(&mutexArray[threadData->idx]);

        int selectReturn = select(FD_SETSIZE, &readySockets, NULL, NULL, &tv);
        BTruckers::Server::Utils::CheckResponse(selectReturn, "Select failed.");
        if(selectReturn == 0)
        {
            //if we have a timeout well... we will just skip for the next one
            continue;
        }

        pthread_mutex_lock(&mutexArray[threadData->idx]);
        //this should not take very long because we can have max 10 client/thread
        for(int idx=0;idx<threadData->count;idx++)
        {
            //this wasn't the socket that hit so we continue
            if(!FD_ISSET(threadData->sockets[idx], &threadData->currentSockets))
                continue;

            LOG_DEBUG("[ THREAD %d ] Client '%d' is ready.",threadData->idx, threadData->sockets[idx]);
            std::string recvMessage = BTruckers::Shared::Protocols::TCP::Receive(threadData->sockets[idx]); 
            
            //in case the client doesn't have anything more to tell us.
            if(recvMessage == "")
            {
                LOG_INFO("[ THREAD %d ] Ended the connection with client '%d'.",threadData->idx, threadData->sockets[idx]);
                close(threadData->sockets[idx]);
                FD_CLR(threadData->sockets[idx], &threadData->currentSockets);
                idx--;
                threadData->count--;
                threadData->sockets.erase(threadData->sockets.begin()+idx);
                continue;
            }

            //here we will handle logic for the command.
            LOG_DEBUG("[ THREAD %d ] Client '%d' send us: '%s'",threadData->idx, threadData->sockets[idx], recvMessage.c_str());
            
            BTruckers::Shared::Structures::Message request = cpv.Parse(recvMessage); 
            std::string response = BTruckers::Server::Commands::Handler(request, &db);
            if(!BTruckers::Shared::Protocols::TCP::Send(threadData->sockets[idx],response))
            {
                LOG_ERROR("[ THREAD %d ] Failed to send response to client '%d'",threadData->idx, threadData->sockets[idx]);
            }
            //end of for loop
        }
        pthread_mutex_unlock(&mutexArray[threadData->idx]);
    }
    return nullptr;
}

int main()
{
    //handle the appropriate signal
    signal(SIGINT, BTruckers::Server::Utils::SignalHandler);

    //check for debug
    if(DEBUG_MODE == true)
    {
        
        Logger::SetLoggingLevel(BTruckers::Shared::Enums::LoggingLevel::DEBUG);
        LOG_DEBUG("Application is now running in verbose mode...");
    }
    LOG_DEBUG("Started with pid %d", getpid());


    BTruckers::Server::Core::Server server;

    
    BTruckers::Server::Structures::Thread* ThreadInformation = new BTruckers::Server::Structures::Thread[THREAD_POOL_SIZE];
    pthread_t threadPool[THREAD_POOL_SIZE];

    for(int idx=0;idx<THREAD_POOL_SIZE;idx++)
    {
        pthread_mutex_init(&mutexArray[idx], NULL);

        ThreadInformation[idx].idx = idx;
        ThreadInformation[idx].serverSocket = server.getServerSocket();
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
        LOG_INFO("New client connection: %d and sending to to thread %d", clientIDX, ThreadInformation[correspondingIDXtoMin].idx);
        pthread_mutex_lock(&mutexArray[correspondingIDXtoMin]);
        ThreadInformation[correspondingIDXtoMin].count++;
        ThreadInformation[correspondingIDXtoMin].sockets.push_back(clientIDX);
        FD_SET(clientIDX,&ThreadInformation[correspondingIDXtoMin].currentSockets);
        pthread_mutex_unlock(&mutexArray[correspondingIDXtoMin]);
    }

    return 0;
}
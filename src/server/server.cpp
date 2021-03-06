#include "BTRCommon.h"
#include "BTRShared.h"
#include "Server.h"
#include "Logger.h"
#include "protocols/TCP.h"
#include "models/Entertainment.h"
#include "CPV.h"
#include "DBHandler.h"
#include <signal.h>
pthread_mutex_t mutexArray[THREAD_POOL_SIZE];
pthread_mutex_t globalMutex = PTHREAD_MUTEX_INITIALIZER;
BTruckers::Server::Structures::Thread* ThreadInformation;
BTruckers::Server::Core::CPV cpv;
std::vector<BTruckers::Server::Structures::BroadcasterMessages> messages;
volatile sig_atomic_t broadcastToClients = false;

void broadcasterAlarm( int sig ) {
    //just to avoid warnings
    sig = sig;
    broadcastToClients = true;
    pthread_cond_signal(&BTruckers::Server::Core::Broadcaster::waitForData);
}

void* BroadcasterThread(void* arg)
{
    //just to avoid warnings
    arg = (void*) arg;
    signal(SIGALRM, broadcasterAlarm);

    //starting a database connection
    BTruckers::Server::Core::DBHandler db;

    LOG_INFO("[BROADCASTER] Initialized.");

    BTruckers::Shared::Structures::Message msg;
    msg.token.identifier = APPLICATION_SECRET;
    msg.token.validator = APPLICATION_SECRET;
    msg.command = "Broadcast";
    msg.success = true;
    alarm(1);

    while(BTruckers::Server::Core::serverRunning)
    {
        msg.payload = "";
        pthread_mutex_lock(&BTruckers::Server::Core::Broadcaster::broadcasterLock);
        if(BTruckers::Server::Core::Broadcaster::broadcasterQueue.empty())
        {
            pthread_cond_wait(&BTruckers::Server::Core::Broadcaster::waitForData,&BTruckers::Server::Core::Broadcaster::broadcasterLock);
        }
        pthread_mutex_unlock(&BTruckers::Server::Core::Broadcaster::broadcasterLock);

        if(broadcastToClients)
        {
            LOG_DEBUG("We will append some messages to the queue!");
            BTruckers::Server::Models::Entertainment::AddToBroadcasterQueue(&db);
        }

        pthread_mutex_lock(&BTruckers::Server::Core::Broadcaster::broadcasterLock);
        while(!BTruckers::Server::Core::Broadcaster::broadcasterQueue.empty())
        {
            msg.payload = msg.payload + BTruckers::Server::Core::Broadcaster::broadcasterQueue.front() + "|";
            BTruckers::Server::Core::Broadcaster::broadcasterQueue.pop();
        }
        pthread_mutex_unlock(&BTruckers::Server::Core::Broadcaster::broadcasterLock);

        if(msg.payload == "")
            continue; 
            
        for(int idx = 0; idx < THREAD_POOL_SIZE; ++idx)
        {
            BTruckers::Server::Utils::CheckResponse(pthread_mutex_lock(&mutexArray[ThreadInformation[idx].idx]), "Failed to acquire lock in broadcaster thread.");
            for(int i = 0; i < ThreadInformation[idx].count; ++i)
            {
                if(ThreadInformation[idx].sockets[i].userUUID == "")
                {
                    LOG_DEBUG("[ BROADCASTER ] User on socket %d is not logged in. Skipping...", ThreadInformation[idx].sockets[i].socketId);
                    continue;
                }
                std::string response = BTruckers::Server::Commands::Handler(msg, &db);
                if(!BTruckers::Shared::Protocols::TCP::Send(ThreadInformation[idx].sockets[i].socketId,response))
                {
                    LOG_ERROR("[ BROADCASTER ] Failed to send message to client with socket '%d'",ThreadInformation[idx].sockets[i].socketId);
                }
            }
            pthread_mutex_unlock(&mutexArray[ThreadInformation[idx].idx]);
        }


        if(broadcastToClients)
        {
            broadcastToClients = false;
            alarm(60);
        }
    }

    LOG_INFO("[ BROADCASTER ] Thread is now closing...");
    return nullptr;
}

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
    LOG_INFO("[ THREAD %d ] I'm initialized now.", threadData->idx);
   
    while(BTruckers::Server::Core::serverRunning)
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
            if(!FD_ISSET(threadData->sockets[idx].socketId, &readySockets))
                continue;

            LOG_DEBUG("[ THREAD %d ] Client '%d' is ready.",threadData->idx, threadData->sockets[idx].socketId);
            std::string recvMessage = BTruckers::Shared::Protocols::TCP::Receive(threadData->sockets[idx].socketId); 
            
            //in case the client doesn't have anything more to tell us.
            if(recvMessage == "")
            {
                LOG_INFO("[ THREAD %d ] Ended the connection with client '%d'.",threadData->idx, threadData->sockets[idx].socketId);
                close(threadData->sockets[idx].socketId);
                FD_CLR(threadData->sockets[idx].socketId, &threadData->currentSockets);
                threadData->sockets.erase(threadData->sockets.begin()+idx);
                threadData->count--;
                idx--;
                continue;
            }

            //here we will handle logic for the command.
            LOG_DEBUG("[ THREAD %d ] Client '%d' send us: '%s'",threadData->idx, threadData->sockets[idx].socketId, recvMessage.c_str());
            
            BTruckers::Shared::Structures::Message request = cpv.Parse(recvMessage);
            // std::string userUUID = ""; 
            std::string response = BTruckers::Server::Commands::Handler(request, &db);
            //getting an internal state for the broadcaster function
            threadData->sockets[idx].userUUID = request.userUUID;
            LOG_DEBUG("[ THREAD %d ] User uuid is: %s",threadData->idx, threadData->sockets[idx].userUUID.c_str());

            if(!BTruckers::Shared::Protocols::TCP::Send(threadData->sockets[idx].socketId,response))
            {
                LOG_ERROR("[ THREAD %d ] Failed to send response to client '%d'",threadData->idx, threadData->sockets[idx].socketId);
            }
            //end of for loop
        }
        pthread_mutex_unlock(&mutexArray[threadData->idx]);
    }

    LOG_INFO("[ THREAD %d ] Warm shutdown started...", threadData->idx);
    for(int idx = 0; idx<threadData->count; ++idx)
    {
        close(threadData->sockets[idx].socketId);
    }

    LOG_INFO("[ THREAD %d ] Shutdown complete...", threadData->idx);
    close(threadData->serverSocket);
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

    
    pthread_t threadPool[THREAD_POOL_SIZE];
    ThreadInformation = new BTruckers::Server::Structures::Thread[THREAD_POOL_SIZE];

    for(int idx=0;idx<THREAD_POOL_SIZE;idx++)
    {
        if(pthread_mutex_init(&mutexArray[idx], NULL) != 0)
        {
            LOG_CRITICAL("Failed to create a lock. Exiting.");
            exit(-1);
        }

        ThreadInformation[idx].idx = idx;
        ThreadInformation[idx].serverSocket = server.getServerSocket();
        if(pthread_create(&threadPool[idx], nullptr, &threadFunction, (void*) (ThreadInformation+idx))!=0)
        {
            LOG_CRITICAL("Failed to create a thread. Exiting.");
            exit(-1);
        }
    }

    pthread_t broadcasterThread;
    if(pthread_create(&broadcasterThread, nullptr, &BroadcasterThread, (void*) (ThreadInformation))!=0)
    {
        LOG_CRITICAL("Failed to create broadcaster thread. Exiting.");
        exit(-1);
    }

    while(BTruckers::Server::Core::serverRunning)
    {
        int clientIDX = server.InitiateConnectionWithClient();
        
        if(clientIDX == -1)
            continue; 
            
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
        BTruckers::Server::Structures::SocketData newSock;
        newSock.socketId = clientIDX;
        newSock.userUUID = "";
        ThreadInformation[correspondingIDXtoMin].count++;
        ThreadInformation[correspondingIDXtoMin].sockets.push_back(newSock);
        FD_SET(clientIDX,&ThreadInformation[correspondingIDXtoMin].currentSockets);
        pthread_mutex_unlock(&mutexArray[correspondingIDXtoMin]);
    }

    LOG_INFO("[ MAIN ] Warm shutdown started. Waiting for all threads to finish...");
    pthread_cond_signal(&BTruckers::Server::Core::Broadcaster::waitForData);

    pthread_join(broadcasterThread, NULL);
    LOG_DEBUG("Broadcaster thread finished...");

    for(int idx=0;idx<THREAD_POOL_SIZE;idx++)
    {
        pthread_join(threadPool[idx], NULL);
        LOG_DEBUG("Thread %d finished",idx);
    }

    LOG_INFO("Bye bye :D");
    return 0;
}
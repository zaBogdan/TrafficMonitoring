#include "Broadcaster.h"

pthread_mutex_t BTruckers::Server::Core::Broadcaster::broadcasterLock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t BTruckers::Server::Core::Broadcaster::waitForData = PTHREAD_COND_INITIALIZER;
std::queue<std::string> BTruckers::Server::Core::Broadcaster::broadcasterQueue;
bool BTruckers::Server::Core::Broadcaster::isInit = false;

void BTruckers::Server::Core::Broadcaster::Init()
{
    if(isInit)
    {
        LOG_ERROR("You can't initialize 2 Broadcaster classes");
        exit(1);
    }
    Broadcaster::isInit = true;
}

void BTruckers::Server::Core::Broadcaster::PushMessageToQueue(std::string message)
{
    if(!isInit)
        Broadcaster::Init();
    pthread_mutex_lock(&broadcasterLock);
    broadcasterQueue.push(message);
    pthread_cond_signal(&waitForData);
    pthread_mutex_unlock(&broadcasterLock);
}
// void BTruckers::Server::Broadcaster::PushMessageToQueue(std::string message)
// {
//     pthread_mutex_lock(&broadcasterLock);
//     broadcasterQueue.push(message);
//     pthread_cond_signal(&waitForData);
//     pthread_mutex_unlock(&broadcasterLock);
// }
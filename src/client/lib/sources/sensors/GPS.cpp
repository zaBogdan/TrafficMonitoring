#include "sensors/GPSSensor.h"

// TODO
BTruckers::Client::Sensors::GPS::GPS()
{
    LOG_INFO("Initializing hardware GPS sensor.");
    
    this->longitute = 471737992;
    this->latitude = 275719684;
    
    LOG_INFO("The GPS metric is: %lld %lld", this->longitute, this->latitude);
}

std::pair<long long, long long> BTruckers::Client::Sensors::GPS::Read()
{
    this->Update();
    LOG_DEBUG("New coords are: %lld,%lld", this->longitute, this->latitude);
    return std::pair<long long, long long>(this->longitute, this->latitude);
}

void BTruckers::Client::Sensors::GPS::Update()
{
    // this->longitute 
    std::srand(std::time(nullptr));
    int randomMovement = 1 + std::rand() % 10;

    this->longitute = this->longitute + ((randomMovement % 2 == 0) ? randomMovement : - randomMovement) * 10000;
    
    randomMovement = 1 + std::rand() % 10;
    
    this->latitude = this->latitude + ((randomMovement % 2 == 0) ? randomMovement : - randomMovement) * 10000;

}

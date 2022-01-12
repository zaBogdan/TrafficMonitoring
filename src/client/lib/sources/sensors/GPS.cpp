#include "sensors/GPSSensor.h"

// TODO
BTruckers::Client::Sensors::GPS::GPS()
{
    LOG_INFO("Initializing hardware GPS sensor.");
    
    this->position.longitute = 47.1737992;
    this->position.latitude = 27.5719684;
    
    LOG_INFO("The GPS metric is: %.6f %.6f", this->position.longitute, this->position.latitude);
}

BTruckers::Shared::Structures::Cords BTruckers::Client::Sensors::GPS::Read()
{
    this->Update();
    LOG_DEBUG("The GPS metric is: %.6f %.6f", this->position.longitute, this->position.latitude);
    return this->position;
}

void BTruckers::Client::Sensors::GPS::Update()
{
    // this->longitute 
    std::srand(std::time(nullptr));
    int randomMovement = 1 + std::rand() % 10;

    float data = (float)((randomMovement % 2 == 0) ? randomMovement : - randomMovement) / 100;
    LOG_DEBUG("The data is: %.6f", data);
    this->position.longitute = this->position.longitute + data;
    
    randomMovement = 1 + std::rand() % 10;
    data = (float)((randomMovement % 2 == 0) ? randomMovement : - randomMovement) / 100;
    this->position.latitude = this->position.latitude + data;

}

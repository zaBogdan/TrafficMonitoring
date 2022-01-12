#include "sensors/GPSSensor.h"

BTruckers::Shared::Structures::Cords BTruckers::Client::Sensors::GPS::position;
bool BTruckers::Client::Sensors::GPS::isInit = false;

BTruckers::Client::Sensors::GPS::GPS()
{
    if(isInit == true)
    {
        LOG_ERROR("Can't initialize two GPS sensors!");
        exit(0);
    }
    LOG_INFO("Initializing hardware GPS sensor.");
    
    BTruckers::Client::Sensors::GPS::position.longitute = 47.1737992;
    BTruckers::Client::Sensors::GPS::position.latitude = 27.5719684;
    
    BTruckers::Client::Sensors::GPS::Update();

    LOG_INFO("The GPS metric is: %.6f %.6f", BTruckers::Client::Sensors::GPS::position.longitute, BTruckers::Client::Sensors::GPS::position.latitude);
}

BTruckers::Shared::Structures::Cords BTruckers::Client::Sensors::GPS::Read()
{
    BTruckers::Client::Sensors::GPS::Update();
    LOG_DEBUG("The GPS metric is: %.6f %.6f", BTruckers::Client::Sensors::GPS::position.longitute, BTruckers::Client::Sensors::GPS::position.latitude);
    return BTruckers::Client::Sensors::GPS::position;
}

void BTruckers::Client::Sensors::GPS::Update()
{
    // BTruckers::Client::Sensors::GPS::longitute 
    std::srand(std::time(nullptr));
    int randomMovement = 1 + std::rand() % 10;

    float data = (float)((randomMovement % 2 == 0) ? randomMovement : - randomMovement) / 100;
    LOG_DEBUG("The data is: %.6f", data);
    BTruckers::Client::Sensors::GPS::position.longitute = BTruckers::Client::Sensors::GPS::position.longitute + data;
    
    randomMovement = 1 + std::rand() % 10;
    data = (float)((randomMovement % 2 == 0) ? randomMovement : - randomMovement) / 100;
    BTruckers::Client::Sensors::GPS::position.latitude = BTruckers::Client::Sensors::GPS::position.latitude + data;

}

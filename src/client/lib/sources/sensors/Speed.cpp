#include "sensors/SpeedSensor.h"

BTruckers::Client::Sensors::Speed::Speed()
{
    LOG_INFO("Initializing hardware SPEED sensor.");
    std::srand(std::time(nullptr));
    this->speedData = 50 + std::rand() % 30;
    LOG_INFO("The speed metric is: %d", this->speedData);
}

int BTruckers::Client::Sensors::Speed::Read()
{
    this->Update();
    LOG_INFO("New speed is: %d", this->speedData);
    return this->speedData;
}

void BTruckers::Client::Sensors::Speed::Update()
{
    std::srand(std::time(nullptr));
    int maxSpeedDiff = 1 + std::rand()%15;
    this->speedData = std::max(0,
        this->speedData - 
        std::rand() % maxSpeedDiff +
        std::rand() % maxSpeedDiff 
    );
}
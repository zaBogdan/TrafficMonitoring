#include "../includes/Logger.h"

unsigned int Logger::logging_level = BTrucks::Utils::LoggingLevel::WARNING;

void Logger::SetLoggingLevel(BTrucks::Utils::LoggingLevel::Type level)
{
    if(level>=BTrucks::Utils::LoggingLevel::DEBUG && level<=BTrucks::Utils::LoggingLevel::CRITICAL)
    {
        Logger::logging_level = level;
    }else{
        Logger::logging_level = BTrucks::Utils::LoggingLevel::INFO;
    }
}

void Logger::Critical(std::string msg)
{
    Logger::Print(BTrucks::Utils::LoggingLevel::CRITICAL, msg);
}
void Logger::Error(std::string msg)
{
    Logger::Print(BTrucks::Utils::LoggingLevel::ERROR, msg);
}
void Logger::Warning(std::string msg)
{
    Logger::Print(BTrucks::Utils::LoggingLevel::WARNING, msg);
}
void Logger::Info(std::string msg)
{
    Logger::Print(BTrucks::Utils::LoggingLevel::INFO, msg);
}
void Logger::Debug(std::string msg)
{
    Logger::Print(BTrucks::Utils::LoggingLevel::DEBUG, msg);
}


void Logger::Print(BTrucks::Utils::LoggingLevel::Type level, std::string msg)
{
    if(level >= Logger::logging_level)
        std::cout << Logger::GetLevelString(level) << "[ Server ] " << msg << '\n';
}

std::string Logger::GetLevelString(BTrucks::Utils::LoggingLevel::Type level)
{
    switch(level){
        case BTrucks::Utils::LoggingLevel::CRITICAL:
            return "[ CRITICAL ]";
        case BTrucks::Utils::LoggingLevel::ERROR:
            return "[ ERROR ]";
        case BTrucks::Utils::LoggingLevel::WARNING:
            return "[ WARNING ]";
        case BTrucks::Utils::LoggingLevel::INFO:
            return "[ INFO ]";
        case BTrucks::Utils::LoggingLevel::DEBUG:
            return "[ DEBUG ]";
        default:
            return "[ NONE ]";
    }
}
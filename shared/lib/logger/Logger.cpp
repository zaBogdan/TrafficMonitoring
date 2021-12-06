#include "../includes/Logger.h"

unsigned int Logger::logging_level = BTrucksShared::Utils::LoggingLevel::INFO;

void Logger::SetLoggingLevel(BTrucksShared::Utils::LoggingLevel::Type level)
{
    if(level>=BTrucksShared::Utils::LoggingLevel::DEBUG && level<=BTrucksShared::Utils::LoggingLevel::CRITICAL)
    {
        Logger::logging_level = level;
    }else{
        Logger::logging_level = BTrucksShared::Utils::LoggingLevel::INFO;
    }
}

void Logger::Critical(std::string msg)
{
    Logger::Print(BTrucksShared::Utils::LoggingLevel::CRITICAL, msg);
}
void Logger::Error(std::string msg)
{
    Logger::Print(BTrucksShared::Utils::LoggingLevel::ERROR, msg);
}
void Logger::Warning(std::string msg)
{
    Logger::Print(BTrucksShared::Utils::LoggingLevel::WARNING, msg);
}
void Logger::Info(std::string msg)
{
    Logger::Print(BTrucksShared::Utils::LoggingLevel::INFO, msg);
}
void Logger::Debug(std::string msg)
{
    Logger::Print(BTrucksShared::Utils::LoggingLevel::DEBUG, msg);
}


void Logger::Print(BTrucksShared::Utils::LoggingLevel::Type level, std::string msg)
{
    if(level >= Logger::logging_level)
        printf("%s[ SERVER ] %s\n", Logger::GetLevelString(level).c_str(), msg.c_str());
}

std::string Logger::GetLevelString(BTrucksShared::Utils::LoggingLevel::Type level)
{
    switch(level){
        case BTrucksShared::Utils::LoggingLevel::CRITICAL:
            return "[ CRITICAL ]";
        case BTrucksShared::Utils::LoggingLevel::ERROR:
            return "[ ERROR ]";
        case BTrucksShared::Utils::LoggingLevel::WARNING:
            return "[ WARNING ]";
        case BTrucksShared::Utils::LoggingLevel::INFO:
            return "[ INFO ]";
        case BTrucksShared::Utils::LoggingLevel::DEBUG:
            return "[ DEBUG ]";
        default:
            return "[ NONE ]";
    }
}
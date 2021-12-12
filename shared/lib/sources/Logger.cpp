#include "Logger.h"

unsigned int Logger::logging_level = BTRShared::Utils::LoggingLevel::INFO;

void Logger::SetLoggingLevel(BTRShared::Utils::LoggingLevel::Type level)
{
    if(level>=BTRShared::Utils::LoggingLevel::DEBUG && level<=BTRShared::Utils::LoggingLevel::CRITICAL)
    {
        Logger::logging_level = level;
    }else{
        Logger::logging_level = BTRShared::Utils::LoggingLevel::INFO;
    }
}

void Logger::Critical(std::string msg)
{
    Logger::Print(BTRShared::Utils::LoggingLevel::CRITICAL, msg);
}
void Logger::Error(std::string msg)
{
    Logger::Print(BTRShared::Utils::LoggingLevel::ERROR, msg);
}
void Logger::Warning(std::string msg)
{
    Logger::Print(BTRShared::Utils::LoggingLevel::WARNING, msg);
}
void Logger::Info(std::string msg)
{
    Logger::Print(BTRShared::Utils::LoggingLevel::INFO, msg);
}
void Logger::Debug(std::string msg)
{
    Logger::Print(BTRShared::Utils::LoggingLevel::DEBUG, msg);
}


void Logger::Print(BTRShared::Utils::LoggingLevel::Type level, std::string msg)
{
    if(level >= Logger::logging_level)
        printf("%s - %s[ SERVER ] %s\n",BTRShared::Utils::CurrentDateTime().c_str(), Logger::GetLevelString(level).c_str(), msg.c_str());
}

std::string Logger::GetLevelString(BTRShared::Utils::LoggingLevel::Type level)
{
    switch(level){
        case BTRShared::Utils::LoggingLevel::CRITICAL:
            return "[ CRITICAL ]";
        case BTRShared::Utils::LoggingLevel::ERROR:
            return "[ ERROR ]";
        case BTRShared::Utils::LoggingLevel::WARNING:
            return "[ WARNING ]";
        case BTRShared::Utils::LoggingLevel::INFO:
            return "[ INFO ]";
        case BTRShared::Utils::LoggingLevel::DEBUG:
            return "[ DEBUG ]";
        default:
            return "[ NONE ]";
    }
}
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

void Logger::Print(BTRShared::Utils::LoggingLevel::Type level, const char* fmt...)
{
    if(level < Logger::logging_level)
        return;
    printf("%s - %s[ %s ] ",BTRShared::Utils::CurrentDateTime().c_str(),Logger::GetLevelString(level).c_str(), APPLICATION_NAME);
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    printf("\n");
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
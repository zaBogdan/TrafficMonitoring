#include "Logger.h"


unsigned int Logger::logging_level = BTruckers::Shared::Enums::LoggingLevel::INFO;

void Logger::SetLoggingLevel(BTruckers::Shared::Enums::LoggingLevel::Type level)
{
    if(level>=BTruckers::Shared::Enums::LoggingLevel::DEBUG && level<=BTruckers::Shared::Enums::LoggingLevel::CRITICAL)
    {
        Logger::logging_level = level;
    }else{
        Logger::logging_level = BTruckers::Shared::Enums::LoggingLevel::INFO;
    }
}

void Logger::Print(BTruckers::Shared::Enums::LoggingLevel::Type level, const char* fmt...)
{
    if(level < Logger::logging_level)
        return;
    printf("%s - %s[ %s ] ",BTruckers::Shared::Utils::CurrentDateTime().c_str(),Logger::GetLevelString(level).c_str(), APPLICATION_NAME);
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    printf("\n");
}

std::string Logger::GetLevelString(BTruckers::Shared::Enums::LoggingLevel::Type level)
{
    switch(level){
        case BTruckers::Shared::Enums::LoggingLevel::CRITICAL:
            return "[ CRITICAL ]";
        case BTruckers::Shared::Enums::LoggingLevel::ERROR:
            return "[ ERROR ]";
        case BTruckers::Shared::Enums::LoggingLevel::WARNING:
            return "[ WARNING ]";
        case BTruckers::Shared::Enums::LoggingLevel::INFO:
            return "[ INFO ]";
        case BTruckers::Shared::Enums::LoggingLevel::DEBUG:
            return "[ DEBUG ]";
        default:
            return "[ NONE ]";
    }
}
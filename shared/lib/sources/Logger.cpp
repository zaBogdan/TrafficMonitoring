#include "Logger.h"


unsigned int Logger::logging_level = BTruckers::Shared::Enums::LoggingLevel::INFO;
FILE* Logger::fp = nullptr;

Logger::Logger()
{
    std::string filename = "./logs/" APPLICATION_NAME ".txt";
    Logger::fp = fopen(filename.c_str(), "w+");
    // LOG_DEBUG("Initialized the file.");
    printf("I've initialized the file.\n");
}

Logger::~Logger()
{
    fclose (Logger::fp);
}


void Logger::SetLoggingLevel(BTruckers::Shared::Enums::LoggingLevel::Type level)
{
    if(Logger::fp == nullptr)
    {
        new Logger();
    }

    if(level>=BTruckers::Shared::Enums::LoggingLevel::DEBUG && level<=BTruckers::Shared::Enums::LoggingLevel::CRITICAL)
    {
        Logger::logging_level = level;
    }else{
        Logger::logging_level = BTruckers::Shared::Enums::LoggingLevel::INFO;
    }
}

void Logger::Print(BTruckers::Shared::Enums::LoggingLevel::Type level, const char* fmt...)
{
    if(Logger::fp == nullptr)
    {
        new Logger();
    }
    
    if(level < Logger::logging_level)
        return;

    fflush(stdout);
    printf("%s - %s[ %s ] ",BTruckers::Shared::Utils::CurrentDateTime().c_str(),Logger::GetLevelString(level).c_str(), APPLICATION_NAME);
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    fflush(stdout);
    printf("\n");

    fprintf(Logger::fp, "%s - %s[ %s ] ",BTruckers::Shared::Utils::CurrentDateTime().c_str(),Logger::GetLevelString(level).c_str(), APPLICATION_NAME);
    va_start(args, fmt);
    vfprintf(Logger::fp,fmt, args);
    va_end(args);
    fprintf(Logger::fp,"\n");
}

std::string Logger::GetLevelString(BTruckers::Shared::Enums::LoggingLevel::Type level)
{
    if(Logger::fp == nullptr)
    {
        new Logger();
    }

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
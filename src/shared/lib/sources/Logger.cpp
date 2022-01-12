#include "Logger.h"


unsigned int Logger::logging_level = BTruckers::Shared::Enums::LoggingLevel::INFO;
FILE* Logger::fp = nullptr;
pthread_mutex_t Logger::loggerMutexLock = PTHREAD_MUTEX_INITIALIZER;

Logger::Logger()
{
    if(Logger::fp != nullptr)
    {
        LOG_WARNING("You can't have two logger classes");
        return;
    }

    if(pthread_mutex_init(&Logger::loggerMutexLock, NULL) != 0)
    {
        LOG_CRITICAL("Failed to create logger mutex lock. Exiting.");
        exit(-1);
    }

    setbuf(stdout,NULL);
    setbuf(stderr,NULL);
    std::string filename = DUMP_LOGS_TO APPLICATION_NAME;
    filename += "-"+BTruckers::Shared::Utils::CurrentDateTime("%F-%X") + ".txt";
    Logger::fp = fopen(filename.c_str(), "w+");
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
    pthread_mutex_lock(&Logger::loggerMutexLock);
    printf("%s - %s[ %s ] ",BTruckers::Shared::Utils::CurrentDateTime().c_str(),Logger::GetLevelString(level).c_str(), APPLICATION_NAME);
    pthread_mutex_unlock(&Logger::loggerMutexLock);
    va_list args;
    va_start(args, fmt);
    pthread_mutex_lock(&Logger::loggerMutexLock);
    vprintf(fmt, args);
    pthread_mutex_unlock(&Logger::loggerMutexLock);
    va_end(args);
    fflush(stdout);
    printf("\n");

    pthread_mutex_lock(&Logger::loggerMutexLock);
    fprintf(Logger::fp, "%s - %s[ %s ] ",BTruckers::Shared::Utils::CurrentDateTime().c_str(),Logger::GetLevelString(level).c_str(), APPLICATION_NAME);
    pthread_mutex_unlock(&Logger::loggerMutexLock);
    va_start(args, fmt);
    pthread_mutex_lock(&Logger::loggerMutexLock);
    vfprintf(Logger::fp,fmt, args);
    pthread_mutex_unlock(&Logger::loggerMutexLock);
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
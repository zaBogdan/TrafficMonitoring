#pragma once
#include "BTRShared.h"
#include <cstdarg>
#include <cstddef>
#include <pthread.h>


#if defined(__CLIENT__)
#define APPLICATION_NAME "CLIENT"
#elif defined(__SERVER__)
#define APPLICATION_NAME "SERVER"
#else
#define APPLICATION_NAME "SHARED"
#endif

#ifndef DUMP_LOGS_TO
#define DUMP_LOGS_TO "../logs/"
#endif

#define LOG_CRITICAL(...) Logger::Print(BTruckers::Shared::Enums::LoggingLevel::CRITICAL, __VA_ARGS__);
#define LOG_ERROR(...) Logger::Print(BTruckers::Shared::Enums::LoggingLevel::ERROR, __VA_ARGS__);
#define LOG_WARNING(...) Logger::Print(BTruckers::Shared::Enums::LoggingLevel::WARNING, __VA_ARGS__);
#define LOG_INFO(...) Logger::Print(BTruckers::Shared::Enums::LoggingLevel::INFO, __VA_ARGS__);
#define LOG_DEBUG(...) Logger::Print(BTruckers::Shared::Enums::LoggingLevel::DEBUG, __VA_ARGS__);


class Logger{
    private:
        static pthread_mutex_t loggerMutexLock;
        static FILE *fp;
        static unsigned int logging_level;
        static std::string GetLevelString(BTruckers::Shared::Enums::LoggingLevel::Type level);
        Logger();
        ~Logger();
    public:
        static void Print(BTruckers::Shared::Enums::LoggingLevel::Type level, const char* fmt...);
        static void SetLoggingLevel(BTruckers::Shared::Enums::LoggingLevel::Type level);
};
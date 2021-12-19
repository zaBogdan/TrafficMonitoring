#pragma once
#include "BTRShared.h"
#include <cstdarg>
#include <cstddef>
#if defined(__CLIENT__)
#define APPLICATION_NAME "CLIENT"
#elif defined(__SERVER__)
#define APPLICATION_NAME "SERVER"
#else
#define APPLICATION_NAME "SHARED"
#endif
#define LOG_CRITICAL(...) Logger::Print(BTRShared::Utils::LoggingLevel::CRITICAL, __VA_ARGS__);
#define LOG_ERROR(...) Logger::Print(BTRShared::Utils::LoggingLevel::ERROR, __VA_ARGS__);
#define LOG_WARNING(...) Logger::Print(BTRShared::Utils::LoggingLevel::WARNING, __VA_ARGS__);
#define LOG_INFO(...) Logger::Print(BTRShared::Utils::LoggingLevel::INFO, __VA_ARGS__);
#define LOG_DEBUG(...) Logger::Print(BTRShared::Utils::LoggingLevel::DEBUG, __VA_ARGS__);


class Logger{
    private:
        static unsigned int logging_level;
        static std::string GetLevelString(BTRShared::Utils::LoggingLevel::Type level);
        Logger();
    public:
        static void Print(BTRShared::Utils::LoggingLevel::Type level, const char* fmt...);
        static void SetLoggingLevel(BTRShared::Utils::LoggingLevel::Type level);
};
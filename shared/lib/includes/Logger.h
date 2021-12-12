#pragma once
#include "BTRShared.h"
#include <cstdarg>
#include <cstddef>

class Logger{
    private:
        static unsigned int logging_level;
        static std::string GetLevelString(BTRShared::Utils::LoggingLevel::Type level);
        static void Print(BTRShared::Utils::LoggingLevel::Type level, std::string msg);
        Logger();
    public:
        static void SetLoggingLevel(BTRShared::Utils::LoggingLevel::Type level);
        static void Critical(std::string msg);
        static void Error(std::string msg);
        static void Warning(std::string msg);
        static void Info(std::string msg);
        static void Debug(std::string msg);
};
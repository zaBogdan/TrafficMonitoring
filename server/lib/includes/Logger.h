#pragma once
#include "BTrucks.h"
#include <cstdarg>
#include <cstddef>

class Logger{
    private:
        static unsigned int logging_level;
        static std::string GetLevelString(BTrucks::Utils::LoggingLevel::Type level);
        static void Print(BTrucks::Utils::LoggingLevel::Type level, std::string msg);
        Logger();
    public:
        static void SetLoggingLevel(BTrucks::Utils::LoggingLevel::Type level);
        static void Critical(std::string msg);
        static void Error(std::string msg);
        static void Warning(std::string msg);
        static void Info(std::string msg);
        static void Debug(std::string msg);
};
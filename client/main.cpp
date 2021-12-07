#include "../shared/lib/includes/BTrucksShared.h"
#include "../shared/lib/includes/Logger.h"
#define DEVELOPMENT_MODE true

void printHelp(char* toolName)
{
    printf("BTRucks Client\n");
    printf("Copyright (c) Bogdan Zavadovschi. All right reserved.\n");
    printf("Usage: %s [serverIP/DNS] [port]\n", toolName);
}

int main(int argc, char *argv[])
{
    if(DEVELOPMENT_MODE == true)
    {
        Logger::SetLoggingLevel(BTrucksShared::Utils::LoggingLevel::DEBUG);
        Logger::Debug("Application is now running in verbose mode...");
    }
    if(argc<2)
    {
        printHelp(argv[0]);
        return 1;
    }
    return 0;
}
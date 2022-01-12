#include "clientCommands.h"

std::string BTruckers::Client::Commands::Craft::Help(std::string payload)
{
    payload = payload;
    //finally build the command 

    printf("-=-=-=-=-=-=-= HELP MENU =-=-=-=-=-=-=-=-\n");
    printf("BTruckers Client\n");
    printf("----> To get started you should either login or register. Use one of these commands:\n");
    printf("--> register <username> <password> <firstname> <lastname> <company> <email>\n");
    printf("--> login <username>:<password>\n");
    printf("\n");
    printf("----> Because we all love to have custom preferences you can customize some things:\n");
    printf("--> enable media|storage\n");
    printf("--> disable media|storage\n");
    printf("\n");
    printf("-----> Help the community to know about what's happing on the road!\n");
    printf("--> incident <type>\n");
    printf("You can choose a type from the list below: \n");
    printf("Visibile Police -- 10\t\t Hidden Police -- 11\n");
    printf("Minor accident -- 20\t\t Major accident -- 21\n");
    printf("Road in construction -- 30\t Bad weather -- 31 \t\t Stopped car -- 33\n");
    printf("Dead body on the road -- 32 \t Pothole on the road -- 34\n");
    printf("Lite traffic -- 40\t\t Heavy traffic -- 41\n");
    printf("\n");
    printf("-----> Are you done driving for today? Use\n");
    printf("--> logout\n");
    printf("--> exit\n");
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");

    //and that's the end.
    return "Help";
}
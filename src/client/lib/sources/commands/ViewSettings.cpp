#include "clientCommands.h"

std::string BTruckers::Client::Commands::Craft::ViewSettings(std::string payload)
{
    payload = payload;
    if(payload != "settings")
        return "";
    
    printf("-=-=-=-=-=-= YOUR SETTINGS =-=-=-=-=-=-\n");
    printf("Media - %s (Receive news from time to time)\n", BTruckers::Client::Core::StorageBox::GetItem("media").c_str());
    printf("Storage - %s (Save your settings for when you run the app next time)\n", BTruckers::Client::Core::StorageBox::GetItem("storage").c_str());
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");


    //and that's the end.
    return "Help";
}
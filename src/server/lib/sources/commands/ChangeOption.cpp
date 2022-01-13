#include "sourceCommands.h"

std::string BTruckers::Server::Commands::Handle::ChangeOption(BTruckers::Server::Core::DBHandler *db, BTruckers::Server::Models::Users *user,std::string payload)
{
    BTruckers::Shared::Structures::KeyValue data = PrimiteTypes::FromString(payload);
    BTruckers::Server::Models::Preferences userPref(db);

    bool should_create = false;
    if(!userPref.FindBy("user_uuid", user->GetField("uuid")))
    {
        should_create = true;
        userPref.UpdateField("user_uuid", user->GetField("uuid"));
    }

    if(data.key != "storage" && data.key != "media")
        return BTruckers::Server::Commands::Craft::CommandFailed("Unknown option! You can have only 'media' or 'storage'!");
    
    if(data.key == "storage")
    {
        data.key = "save_storage";
    }
    userPref.UpdateField(data.key, data.value);
    if(should_create)
    {
        userPref.Create();
    }else{
        userPref.Update();
    }
    userPref.Print();

    std::vector<std::string> response = {payload};
    return BTruckers::Server::Commands::Craft::SetSettings(PrimiteTypes::ToDict(response));
}
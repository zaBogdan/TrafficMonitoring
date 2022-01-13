#include "sourceCommands.h"

std::string BTruckers::Server::Commands::Handle::GetSettings(BTruckers::Server::Core::DBHandler *db, BTruckers::Server::Models::Users *user,std::string payload)
{
    payload = payload;
    BTruckers::Server::Models::Preferences userPref(db);

    // bool should_create = false;
    if(!userPref.FindBy("user_uuid", user->GetField("uuid")))
    {
        return BTruckers::Server::Commands::Craft::CommandFailed("No settings to be restored!");
    }

    std::vector<std::string> response = {
        PrimiteTypes::ToString(userPref.GetField("media"),"media"),
        PrimiteTypes::ToString(userPref.GetField("save_storage"),"storage")
    };
    return BTruckers::Server::Commands::Craft::SetSettings(PrimiteTypes::ToDict(response));
}
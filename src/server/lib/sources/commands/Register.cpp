#include "sourceCommands.h"

std::string BTruckers::Server::Commands::Handle::Register(BTruckers::Server::Core::DBHandler *db,std::string payload)
{
    std::vector<BTruckers::Shared::Structures::KeyValue> data = PrimiteTypes::FromDict(payload);
    BTruckers::Server::Models::Users user(db);

    for(auto _d : data)
    {
        if(_d.key == "username" && user.FindBy("username", _d.value))
            return BTruckers::Server::Commands::Craft::CommandFailed("Username or email already exists in our database!");
        if(_d.key == "email" && user.FindBy("email", _d.value))
            return BTruckers::Server::Commands::Craft::CommandFailed("Username or email already exists in our database!");
        
        user.UpdateField(_d.key, _d.value);
    }

    user.Create();
    return BTruckers::Server::Commands::Craft::SetToken(db, user.GetField("uuid"));
}
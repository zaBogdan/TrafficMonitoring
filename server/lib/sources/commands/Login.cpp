#include "sourceCommands.h"

std::string BTruckers::Server::Commands::Handle::Authentication(BTruckers::Server::Core::DBHandler *db,std::string payload)
{
    std::vector<BTruckers::Shared::Structures::KeyValue> loginCredentials = PrimiteTypes::FromDict(payload);
    std::string username, password;

    for(auto it : loginCredentials)
    {
        if(it.key == "username")
        {
            username = it.value;
            continue;
        }
        if(it.key == "password")
        {
            password = it.value;
            continue;
        }
    }

    if(username == "" || password == "")
    {
        return BTruckers::Server::Commands::Craft::CommandFailed("Wrong input format");
    }

    BTruckers::Server::Models::Users user(db, "username", username);

    //checking if the user exists and if the password matches
    if(user.GetField("uuid") == "" || !user.CheckPassword(password))
    {
        return BTruckers::Server::Commands::Craft::CommandFailed("Wrong username of password");
    }

    //now that everything is alright we will generate the tokens (using user uuid)
    return BTruckers::Server::Commands::Craft::SetToken(db,user.GetField("uuid"));
}
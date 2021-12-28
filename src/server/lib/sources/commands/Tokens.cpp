#include "sourceCommands.h"

std::string BTruckers::Server::Commands::Craft::SetToken(BTruckers::Server::Core::DBHandler *db,std::string payload)
{
    //here i am expecting an uuid, if it won't be the session is useless.
    BTruckers::Server::Models::Tokens token(db);

    std::string validatorRaw = BTruckers::Server::Core::Tokens::Generate();
    std::string identifier =  BTruckers::Server::Core::Tokens::Generate();

    token.UpdateField("user_uuid", payload);
    token.UpdateField("identifier", identifier);

    //adding an extra layer of protection to data tampering
    token.UpdateField("validator", BTruckers::Server::Core::Tokens::SHA256(std::string(APPLICATION_SECRET) + validatorRaw));

    //setting the correct timestamps.
    token.SetTime();

    if(!token.Create())
        return BTruckers::Server::Commands::Craft::CommandFailed("Failed to create a session.");

    token.Print();

    validatorRaw = PrimiteTypes::ToString(validatorRaw, "validator");
    identifier = PrimiteTypes::ToString(identifier, "identifier");

    std::vector<std::string> finalDict {identifier, validatorRaw};
    std::string dict = PrimiteTypes::ToDict(finalDict);

    std::string command = std::string(SETTOKENS_COMMAND) + std::string(":") + dict;

    //to be implemented the logic
    return command;
}
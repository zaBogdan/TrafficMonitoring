#pragma once
#include "BTRCommon.h"
#include "BTRShared.h"
#include "PrimitiveTypes.h"
#include "models/Users.h"
#include "models/Tokens.h"

namespace BTruckers
{
    namespace Server
    {
        namespace Commands{
            //public crc
            static const std::vector<uint32_t> publicRoutes = {0xE500DB4};

            //handler
            uint32_t CheckAuthentication(BTruckers::Shared::Structures::Message message, BTruckers::Server::Core::DBHandler *db);
            std::string Handler(BTruckers::Shared::Structures::Message message, BTruckers::Server::Core::DBHandler *db);


            //start commands code


            //start handle code
            namespace Handle
            {
                std::string Authentication(BTruckers::Server::Core::DBHandler *db, std::string payload);
                std::string TokenValidation(BTruckers::Server::Core::DBHandler *db, std::string payload);
            }
            //end handle code

            //start parse code
            namespace Craft
            {
                std::string SetToken(BTruckers::Server::Core::DBHandler *db, std::string payload);
                std::string CommandFailed(std::string payload);
            }
            //end handle code

            // std::string HandleAuthenticateCommand(std::string payload);
            
            // std::string HandleValidateTokensCommand(std::string payload);
            // std::string ParseIncidentCommand(std::string payload);
            
            // std::string HandleAuthenticateCommand(std::string payload);

            //end commands code
        }
    }
}

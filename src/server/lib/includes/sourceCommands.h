#pragma once
#include "BTRCommon.h"
#include "BTRShared.h"
#include "PrimitiveTypes.h"
#include "models/Users.h"
#include "models/Incidents.h"
#include "models/Tokens.h"

namespace BTruckers
{
    namespace Server
    {
        namespace Commands{
            //public crc
            static const std::vector<uint32_t> publicRoutes = {0xE500DB4};

            //handler
            uint32_t CheckAuthentication(BTruckers::Shared::Structures::Message message, BTruckers::Server::Core::DBHandler *db, BTruckers::Server::Models::Users *user);
            std::string Handler(BTruckers::Shared::Structures::Message& message, BTruckers::Server::Core::DBHandler *db);


            //start commands code


            //start handle code
            namespace Handle
            {
                //public routes
                std::string Authentication(BTruckers::Server::Core::DBHandler *db, std::string payload);
                
                //private routes
                std::string Incident(BTruckers::Server::Core::DBHandler *db, BTruckers::Server::Models::Users *user, std::string payload);

            }
            //end handle code

            //start parse code
            namespace Craft
            {
                std::string SetToken(BTruckers::Server::Core::DBHandler *db, std::string payload);
                std::string CommandFailed(std::string payload);
                std::string CommandSuccess(std::string payload);
            }
            //end commands code
        }
    }
}

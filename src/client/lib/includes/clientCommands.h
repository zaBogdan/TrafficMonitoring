#pragma once
#include "BTRClient.h"
#include "BTRShared.h"
#include "PrimitiveTypes.h"
#include "StorageBox.h"
#include "sensors/GPSSensor.h"

namespace BTruckers{
    namespace Client{
        namespace Commands{
            //handler
            std::string HandleResponse(BTruckers::Shared::Structures::Message message, bool isRequest = true);

            //start commands code
            namespace Handle
            {
                std::string SetTokens(std::string payload);
                std::string SimpleResponse(std::string payload);
                std::string Broadcast(std::string payload);
                std::string SetSettings(std::string payload);
                std::string InvalidateTokens(std::string payload);
            }

            namespace Craft
            {
                std::string Authentication(std::string payload);
                std::string ReportIncident(std::string payload);
                std::string Logout(std::string payload);
                std::string Register(std::string payload);
                std::string Help(std::string payload);
                std::string SwitchPreference(std::string cmd, std::string payload);
                std::string GetSettings(std::string payload);
                std::string SendMetrics(std::string payload);
            }
            //end commands code
        }
    }
}
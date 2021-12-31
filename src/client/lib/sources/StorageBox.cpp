#include "StorageBox.h"

std::unordered_map<std::string,std::string> BTruckers::Client::Core::StorageBox::storage = {};

bool BTruckers::Client::Core::StorageBox::SetItem(std::string key, std::string value)
{
    BTruckers::Client::Core::StorageBox::storage[key] = value;
}

std::string BTruckers::Client::Core::StorageBox::GetItem(std::string key)
{
    std::unordered_map<std::string,std::string>::const_iterator ke = BTruckers::Client::Core::StorageBox::storage.find(key);
    return ((ke == BTruckers::Client::Core::StorageBox::storage.end()) ? "" : ke->second);
}

void BTruckers::Client::Core::StorageBox::Print()
{
    LOG_DEBUG("-=-=-=-=-= Storage Box -=-=-=-=-=");
    for(auto item : BTruckers::Client::Core::StorageBox::storage)
    {
        LOG_DEBUG("%s = '%s'", item.first.c_str(), (item.second == "" ? "(null)" : item.second.c_str()));
    }
    LOG_DEBUG("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");

}
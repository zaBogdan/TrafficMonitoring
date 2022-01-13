#include "StorageBox.h"

std::unordered_map<std::string,std::string> BTruckers::Client::Core::StorageBox::storage = {};
bool BTruckers::Client::Core::StorageBox::isInit = false;

BTruckers::Client::Core::StorageBox::StorageBox()
{
    if(isInit)
    {
        LOG_ERROR("You can't initialize two StorageBox classes!");
        exit(1);
    }
    isInit = true;
    std::fstream t;
    t.open("client.sb", std::fstream::in);
    std::stringstream strStream;
    strStream << t.rdbuf(); //read the file
    std::string str = strStream.str(); 
    t.close();
    LOG_DEBUG("Contents of file: %s", str.c_str());
    if(str == "") return;

    std::vector<BTruckers::Shared::Structures::KeyValue> data =  PrimiteTypes::FromDict(str);

    for(auto k : data)
    {
        BTruckers::Client::Core::StorageBox::storage[k.key] = k.value;
    }

}

bool BTruckers::Client::Core::StorageBox::SetItem(std::string key, std::string value)
{
    if(!isInit) 
        BTruckers::Client::Core::StorageBox();

    BTruckers::Client::Core::StorageBox::storage[key] = value;
    return true;
}

std::string BTruckers::Client::Core::StorageBox::GetItem(std::string key)
{
    if(!isInit) 
        BTruckers::Client::Core::StorageBox();
    std::unordered_map<std::string,std::string>::const_iterator ke = BTruckers::Client::Core::StorageBox::storage.find(key);
    return ((ke == BTruckers::Client::Core::StorageBox::storage.end()) ? "" : ke->second);
}

void BTruckers::Client::Core::StorageBox::Print()
{
    if(!isInit)
        BTruckers::Client::Core::StorageBox();
    LOG_DEBUG("-=-=-=-=-= Storage Box -=-=-=-=-=");
    for(auto item : BTruckers::Client::Core::StorageBox::storage)
    {
        LOG_DEBUG("%s = '%s'", item.first.c_str(), (item.second == "" ? "(null)" : item.second.c_str()));
    }
    LOG_DEBUG("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
}

void BTruckers::Client::Core::StorageBox::DumpToFile()
{
    if(GetItem("storage") == "0")
    {
        LOG_WARNING("You have your storage turned off! To turn in back on use `enable storage`");
        return;
    }
    LOG_INFO("Dumping to 'client.rb' the local storage...");
    std::fstream t;
    std::vector<std::string> data;
    for(auto item : BTruckers::Client::Core::StorageBox::storage)
    {
        if(item.second == "")
            continue;
        data.push_back(PrimiteTypes::ToString(item.second, item.first));
    }

    t.open("client.sb", std::fstream::out);
    t << PrimiteTypes::ToDict(data);
    t.close();
}
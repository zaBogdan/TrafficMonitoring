#include "PrimitiveTypes.h"

std::string PrimiteTypes::ToString(std::string data, std::string key){
    if(key != "")
    {
        key = key + TYPE_SEPARATOR;
    }
    return std::string(BTRShared::Utils::DataTypes::GetType(BTRShared::Utils::DataTypes::STRING)) + key + data;
}

std::string PrimiteTypes::FromString(std::string data){
    if(data[0] == BTRShared::Utils::DataTypes::STRING)
        return data.substr(1);
    return "";
}


std::string PrimiteTypes::ToDict(std::vector<std::string> data, std::string key)
{
    std::string dictData = std::string(BTRShared::Utils::DataTypes::GetType(BTRShared::Utils::DataTypes::DICT)) + "{";
    for(size_t idx = 0; idx < data.size(); idx++)
    {
        dictData = dictData + data[idx] + ",";
    }
    dictData[dictData.length()-1] = '}';
    return dictData;
}

std::string PrimiteTypes::FromDict(std::string data)
{
    return data;
}
#include "PrimitiveTypes.h"

std::string PrimiteTypes::ToString(std::string data, std::string key){
    if(key != "")
    {
        key = key + TYPE_SEPARATOR;
    }
    return std::string(BTRShared::Utils::DataTypes::GetType(BTRShared::Utils::DataTypes::STRING)) + key + data;
}

BTRShared::Utils::KeyValue PrimiteTypes::FromString(std::string data){
    BTRShared::Utils::KeyValue pair;

    if(data[0] != BTRShared::Utils::DataTypes::GetType(BTRShared::Utils::DataTypes::STRING)[0])
        return pair;

    size_t hasKey = data.find(TYPE_SEPARATOR);
    if(hasKey == std::string::npos)
    {
        pair.value = data.substr(1);
        return pair;
    }

    pair.key = data.substr(1,hasKey-1);
    pair.value = data.substr(hasKey+1);
    
    return pair;
}


std::string PrimiteTypes::ToDict(std::vector<std::string> data)
{
    std::string dictData = std::string(BTRShared::Utils::DataTypes::GetType(BTRShared::Utils::DataTypes::DICT)) + "{";
    for(size_t idx = 0; idx < data.size(); idx++)
    {
        dictData = dictData + data[idx] + ",";
    }
    dictData[dictData.length()-1] = '}';
    return dictData;
}

std::vector<BTRShared::Utils::KeyValue> PrimiteTypes::FromDict(std::string data)
{
    std::vector<BTRShared::Utils::KeyValue> parsedDict = {};
    
    //checking to have the correct type
    if(data[0] != BTRShared::Utils::DataTypes::GetType(BTRShared::Utils::DataTypes::DICT)[0])
        return parsedDict;

    //checking if we have right delimiters
    if(data.find("{") != 1 || data.find("}")!= data.length()-1)
        return parsedDict;

    //removing the d{} from data.
    data = data.substr(2, data.length()-3);
    printf("New dict: %s\n", data.c_str());

    //parsing the dict by commas
    size_t tokenizer = data.find(",");
    while(tokenizer != std::string::npos)
    {
        //getting all KeyValue data
        parsedDict.push_back(PrimiteTypes::DynamicParsing(data.substr(0, tokenizer)));
        //removing current element from dict
        data = data.substr(tokenizer+1);
        //find next
        tokenizer = data.find(",");
    }
    parsedDict.push_back(PrimiteTypes::DynamicParsing(data.substr(0, tokenizer)));
    
    return parsedDict;
}

//private methods
BTRShared::Utils::KeyValue PrimiteTypes::DynamicParsing(std::string data)
{
    BTRShared::Utils::KeyValue pair;
    char dataType = data[0];
    if(dataType == BTRShared::Utils::DataTypes::GetType(BTRShared::Utils::DataTypes::STRING)[0])
        return PrimiteTypes::FromString(data);
    return pair;
}

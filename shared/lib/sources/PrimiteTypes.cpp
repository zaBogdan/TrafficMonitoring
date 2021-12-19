#include "PrimitiveTypes.h"

std::string PrimiteTypes::ToString(std::string data, std::string key){
    if(key != "")
    {
        key = key + TYPE_SEPARATOR;
    }
    return std::string(BTruckers::Shared::Enums::DataTypes::GetType(BTruckers::Shared::Enums::DataTypes::STRING)) + key + data;
}

BTruckers::Shared::Structures::KeyValue PrimiteTypes::FromString(std::string data){
    BTruckers::Shared::Structures::KeyValue pair;

    if(data[0] != BTruckers::Shared::Enums::DataTypes::GetType(BTruckers::Shared::Enums::DataTypes::STRING)[0])
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

std::string PrimiteTypes::ToInteger(int data, std::string key){
    if(key != "")
    {
        key = key + TYPE_SEPARATOR;
    }
    return std::string(BTruckers::Shared::Enums::DataTypes::GetType(BTruckers::Shared::Enums::DataTypes::INT)) + key + std::to_string(data);
}


BTruckers::Shared::Structures::KeyValue PrimiteTypes::FromInteger(std::string data){
    BTruckers::Shared::Structures::KeyValue pair;
    if(data[0] != BTruckers::Shared::Enums::DataTypes::GetType(BTruckers::Shared::Enums::DataTypes::INT)[0])
        return pair;

    size_t hasKey = data.find(TYPE_SEPARATOR);
    if(hasKey == std::string::npos)
    {
        pair.number = std::stoi(data.substr(1));
        return pair;
    }
    pair.key = data.substr(1, hasKey-1);
    pair.number = std::stoi(data.substr(hasKey+1));
    return pair;
}

std::string PrimiteTypes::ToCoordinates(BTruckers::Shared::Structures::Cords data, std::string key)
{
    if(key != "")
    {
        key = key + TYPE_SEPARATOR;
    }

    std::string coordsFormat = "["+std::to_string(data.latitude)+"_"+std::to_string(data.longitute)+"]";

    return std::string(BTruckers::Shared::Enums::DataTypes::GetType(BTruckers::Shared::Enums::DataTypes::COORDINATES)) + key + coordsFormat;
}

BTruckers::Shared::Structures::KeyValue PrimiteTypes::FromCoordinates(std::string data)
{
    BTruckers::Shared::Structures::KeyValue pair;
    if(data[0] != BTruckers::Shared::Enums::DataTypes::GetType(BTruckers::Shared::Enums::DataTypes::COORDINATES)[0])
        return pair;
    
    size_t hasKey = data.find(":");
    if(!hasKey)
    {
        //we will shrink the data for further proccessing.
        data = data.substr(1);
    }else{
        //here we will extract the key and shrink the data further
        pair.key = data.substr(1, hasKey-1);
        data = data.substr(hasKey+1);
    }
    //making sure the format is ok
    if(data.find("[") != 0 && data.find("]") != data.length()-1)
        return pair;

    //now that we have the data like [lat,long] we will split it.
    data = data.substr(1, data.length()-2);

    //checking if we have the right format
    size_t middlePoint = data.find("_");
    if(middlePoint == std::string::npos)
        return pair;

    //final printing    
    pair.coordinates.latitude = std::stod(data.substr(0, middlePoint));
    pair.coordinates.longitute = std::stod(data.substr(middlePoint+1));

    return pair;
}

std::string PrimiteTypes::ToDict(std::vector<std::string> data)
{
    std::string dictData = std::string(BTruckers::Shared::Enums::DataTypes::GetType(BTruckers::Shared::Enums::DataTypes::DICT)) + "{";
    for(size_t idx = 0; idx < data.size(); idx++)
    {
        dictData = dictData + data[idx] + ",";
    }
    dictData[dictData.length()-1] = '}';
    return dictData;
}

std::vector<BTruckers::Shared::Structures::KeyValue> PrimiteTypes::FromDict(std::string data)
{
    std::vector<BTruckers::Shared::Structures::KeyValue> parsedDict = {};
    
    //checking to have the correct type
    if(data[0] != BTruckers::Shared::Enums::DataTypes::GetType(BTruckers::Shared::Enums::DataTypes::DICT)[0])
        return parsedDict;

    //checking if we have right delimiters
    if(data.find("{") != 1 || data.find("}")!= data.length()-1)
        return parsedDict;

    //removing the d{} from data.
    data = data.substr(2, data.length()-3);

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
BTruckers::Shared::Structures::KeyValue PrimiteTypes::DynamicParsing(std::string data)
{
    BTruckers::Shared::Structures::KeyValue pair;
    char dataType = data[0];
    if(dataType == BTruckers::Shared::Enums::DataTypes::GetType(BTruckers::Shared::Enums::DataTypes::STRING)[0])
        return PrimiteTypes::FromString(data);
    if(dataType == BTruckers::Shared::Enums::DataTypes::GetType(BTruckers::Shared::Enums::DataTypes::INT)[0])
        return PrimiteTypes::FromInteger(data);
    if(dataType == BTruckers::Shared::Enums::DataTypes::GetType(BTruckers::Shared::Enums::DataTypes::COORDINATES)[0])
        return PrimiteTypes::FromCoordinates(data);
    return pair;
}

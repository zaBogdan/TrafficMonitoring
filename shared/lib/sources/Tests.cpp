// //test 1
// std::string test1 = PrimiteTypes::ToString("hello");
// printf("[ UNIT TEST 1 ] ToString: %s\n", test1.c_str());
// BTRShared::Utils::KeyValue test2 = PrimiteTypes::FromString(test1);
// printf("[ UNIT TEST 1 ] ");test2.print();

// //test 2
// std::string test3 = PrimiteTypes::ToString("world", "hello");
// printf("[ UNIT TEST 2 ] ToString: %s\n", test3.c_str());
// BTRShared::Utils::KeyValue test4 = PrimiteTypes::FromString(test3);
// printf("[ UNIT TEST 2 ] ");test4.print();

// //test 3
// std::string str1 = PrimiteTypes::ToString("zabogdan", "username");
// std::string str2 = PrimiteTypes::ToString("P@ssw0rd1", "password");
// std::string str3 = PrimiteTypes::ToString("hello", "world");

// std::vector<std::string> Data {str1, str2, str3}; 

// std::string dictionary = PrimiteTypes::ToDict(Data);
// printf("[ UNIT TEST 3 ] ToDict: %s \n", dictionary.c_str());

// //test 4
// std::vector<BTRShared::Utils::KeyValue> parsedDictionary = PrimiteTypes::FromDict(dictionary);
// printf("[ UNIT TEST 4 ] FromDict:\n");
// for(auto x : parsedDictionary)
// {
//     printf("[ UNIT TEST 4 ] ");x.print();
// }

// //test 5
// int type = 10;
// std::string typeInt = PrimiteTypes::ToInteger(type);
// printf("[ UNIT TEST 5 ] Type: %s\n", typeInt.c_str());

// //test 6
// int type2 = 20;
// std::string typeInt2 = PrimiteTypes::ToInteger(type2, "incident");
// printf("[ UNIT TEST 6 ] Type: %s\n", typeInt2.c_str());

// //test 7
// BTRShared::Utils::KeyValue ut7 = PrimiteTypes::FromInteger(typeInt2);
// printf("[ UNIT TEST 7 ] The data is:\n");
// ut7.print();

// //test 8
// std::string str1 = PrimiteTypes::ToString("zabogdan", "username");
// std::string str2 = PrimiteTypes::ToString("P@ssw0rd1", "password");
// std::string str3 = PrimiteTypes::ToInteger(30, "world");

// std::vector<std::string> Data {str1, str2, str3}; 

// std::string dictionary = PrimiteTypes::ToDict(Data);
// printf("[ UNIT TEST 3 ] ToDict: %s \n", dictionary.c_str());

// std::vector<BTRShared::Utils::KeyValue> parsedDictionary = PrimiteTypes::FromDict(dictionary);
// printf("[ UNIT TEST 4 ] FromDict:\n");
// for(auto x : parsedDictionary)
// {
//     printf("[ UNIT TEST 4 ] ");x.print();
// }
// //test9
// BTRShared::Utils::Cords cord;
// cord.latitude = 44.424833;
// cord.longitute = 26.010993;

// //test 3
// std::string str1 = PrimiteTypes::ToString("zabogdan", "username");
// std::string str2 = PrimiteTypes::ToString("P@ssw0rd1", "password");
// std::string str3 = PrimiteTypes::ToCoordinates(cord, "location");
// std::string str4 = PrimiteTypes::ToInteger(300, "world");

// std::vector<std::string> Data {str1, str2, str3,str4}; 

// std::string dictionary = PrimiteTypes::ToDict(Data);
// printf("[ UNIT TEST 3 ] ToDict: %s \n", dictionary.c_str());

// //test 4
// std::vector<BTRShared::Utils::KeyValue> parsedDictionary = PrimiteTypes::FromDict(dictionary);
// printf("[ UNIT TEST 4 ] FromDict:\n");
// for(auto x : parsedDictionary)
// {
//     printf("[ UNIT TEST 4 ] ");x.print();
// }
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
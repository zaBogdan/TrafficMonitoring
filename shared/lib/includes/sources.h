#pragma once
#define MESSAGE_SEPARATOR "|"

namespace BTRShared
{
    namespace Utils{
        namespace LoggingLevel{
            enum Type : unsigned int{
                CRITICAL =  50,
                ERROR =     40,
                WARNING =   30,
                INFO =      20,
                DEBUG =     10
            };
        }
        
        namespace DataTypes{
            enum Type: char{
                NONE =  'n',
                ARRAY =  'a',
                INT =  'i',
                STRING =  's',
                COORDINATES =  'c',
                DICT = 'd'
            };
        }

        // namespace Commands {
        //     enum Type: char{

        //     };
        // }
    }
}
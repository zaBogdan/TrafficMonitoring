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

        namespace CommandsCRC {
            enum Type: uint32_t{
                AUTH = 0xf8deb059,
                AUTHENTICATE = 0xe500db4,
                LOGIN = 0xaa08cb10,

                LOGOUT = 0x35ccf52f,

            };
        }
    }
}
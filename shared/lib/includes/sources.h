#pragma once
#define MESSAGE_SEPARATOR "|"
#define TYPE_SEPARATOR ":"

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
            enum Type: const char{
                NONE,
                ARRAY,
                INT,
                STRING,
                COORDINATES,
                DICT
            };
            inline const char* GetType(Type v)
            {
                switch (v)
                {
                    case ARRAY:   return "a";
                    case INT:   return "i";
                    case STRING:   return "s";
                    case COORDINATES:   return "c";
                    case DICT: return "d";
                    default:      return "n";
                }
            }
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
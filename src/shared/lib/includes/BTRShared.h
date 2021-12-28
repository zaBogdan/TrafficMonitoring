#pragma once
#include <string>
#include <vector>
#include <time.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include "static/constants.h"
#include "Utils.h"

namespace BTruckers{
    namespace Shared{
        
        namespace Core
        {
            //craft parse validate class
            class CPV;
        }

        namespace TCPCommunication
        {
            //goto: Communication.h for definitions
        }

        namespace Utils{
            static inline std::string CurrentDateTime();
            static inline uint32_t CRCValue(std::string s);
            static inline int CheckResponse(int result, const char *errorMessage);
        }
        
        namespace Structures{
            struct Tokens;
            struct Message;
            struct Cords;
            struct KeyValue;
        } 
        
        namespace Enums{
            //start enums code
            namespace LoggingLevel{
                enum Type : unsigned int{
                    CRITICAL =  50, //CRITICAL logging level
                    ERROR =     40, //ERROR logging level
                    WARNING =   30, //WARNING logging level 
                    INFO =      20, //INFO logging level 
                    DEBUG =     10  //DEBUG logging level 
                };
            }
            
            namespace DataTypes{
                enum Type: const char{
                    NONE,
                    INT, //done
                    STRING, //done
                    COORDINATES, //done
                    DICT //done
                };
                inline const char* GetType(Type v)
                {
                    switch (v)
                    {
                        case INT:   return "i";
                        case STRING:   return "s";
                        case COORDINATES:   return "c";
                        case DICT: return "d";
                        default:      return "n";
                    }
                }
            }

            namespace CommandsCRC{
                enum Type: uint32_t{
                    RESPONSE =  0x3e7b0bfb,
                };
            }
            //end enums code
        }
    };
};
#include "static/structures.h"
#include "Logger.h"
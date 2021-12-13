#pragma once
#define MESSAGE_SEPARATOR "|"
#define TYPE_SEPARATOR ":"

#define INCIDENT_COMMAND "Incident"
#define AUTHENTICATE_COMMAND "Authenticate"

namespace BTRShared
{
    namespace Utils{

        struct Cords {
            double longitute = 0.000000, latitude = 0.000000;
            void print(bool prefix = true){
                if(prefix)
                    printf("[ Coordinates ] ");
                printf("%.6f, %.6f", latitude, longitute);
                if(prefix)
                printf("\n");
            } 
        };

        struct KeyValue {
            std::string key="", value="";
            int number = 0;
            Cords coordinates;

            void print(){
                printf("[ KeyValue ] ");
                if(key != "")
                    printf("Key: '%s' ", key.c_str());
                if(value != "")
                    printf("StringValue: '%s' ", value.c_str());
                else if(coordinates.latitude != 0 && coordinates.longitute != 0)
                {
                    printf("Coordinates: ");
                    this->coordinates.print(false);                
                }else{
                    printf("Number: %d", number);
                }
                printf("\n");
            }
        };



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

        namespace Command{
            enum Type: uint32_t{
                RESPONSE =  0x3e7b0bfb,
            };
        }
    }
}
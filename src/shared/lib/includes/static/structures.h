#pragma once
#include "../BTRShared.h"

namespace BTruckers{
    namespace Shared{
        namespace Structures{
                struct Tokens {
                    std::string identifier="", validator="";
                };

                struct Message {
                    Tokens token;
                    std::string command="", payload="", userUUID = "";
                    bool success = false;

                    void print()
                    {
                        if(success == false)
                        {
                            printf("[MessageFormat] Failed to populate the message.");
                            return;
                        }
                        printf("[MessageFormat] Command = %s \n", command.c_str());
                        printf("[MessageFormat] Payload = %s \n", payload.c_str());
                        printf("[MessageFormat] Token.Identifier = %s \n", token.identifier.c_str());
                        printf("[MessageFormat] Token.Validator = %s \n", token.validator.c_str());
                    }
                };

                struct Cords {
                    double longitute = 0.000000, latitude = 0.000000;
                    void print(bool prefix = true){
                        if(prefix)
                            printf("[ Coordinates ] ");
                        printf("%.6f, %.6f", latitude, longitute);
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

                struct TrackChanges{
                    std::string value = "";
                    bool hasChanged = false;
                };
        }       
    }
}


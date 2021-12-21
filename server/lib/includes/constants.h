#pragma once

#define RUNNING_PORT 1337
#define DEBUG_MODE true
#define BACK_LOG 100
#define TOKEN_SIZE 8 //maybe I will change this in the future
#define MAXIMUM_MESSAGE_SIZE 4
#define ERROR_SOCKET -1
#define DATABASE_FILENAME "btruckers.db"
#define CHECK_BREAK(cond, code) {if((cond)) { (code); break;}}
#pragma once

//CHANGE THIS ON YOUR PRODUCTION ENVIRONMENT
#define APPLICATION_SECRET "9ydQs8UcDyZ9D4qIQruPdYw6EW1rcZvK"

//refer to documentation for the number of threads
#define THREAD_POOL_SIZE 3


#define RUNNING_PORT 1337
#define DEBUG_MODE true
#define BACK_LOG 100
#define TOKEN_SIZE 8 //maybe I will change this in the future
#define MAXIMUM_MESSAGE_SIZE 4
#define ERROR_SOCKET -1
#define DATABASE_FILENAME "btruckers.db"
#define DB_FIELDS std::unordered_map<std::string, BTruckers::Shared::Structures::TrackChanges>
#define CHECK_BREAK(cond, code) {if((cond)) { (code); break;}}
#define PARENT_MODE true
#define CHILD_MODE false
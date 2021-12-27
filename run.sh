#!/bin/bash

[[ -z $1 ]] && {
    echo "[ COMPILER ] You must give the name of the instance that you want to run. Options: server or client"; 
    exit 1
}

name=$1
echo "[ COMPILER ] Compilation started..."
time make b$name
[[ $? -ne 0 ]] && {
    echo "[ COMPILER ] Failed to compile the project"
    exit 1;
} 
echo "[ COMPILER ] Starting the instance"
./build/b${name} $2 $3
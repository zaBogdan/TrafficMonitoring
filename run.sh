#!/bin/bash

[[ -z $1 ]] && {
    echo "[ COMPILER ] You must give the name of the instance that you want to run. Options: server or client"; 
    exit 1
}

name=$1
echo "[ COMPILER ] Compilation started..."
g++ -std=c++0x -o ${name}.compiled ${name}/main.cpp $(find ${name}/lib -name '*.cpp') $(find shared/lib -name '*.cpp')
[[ $? -ne 0 ]] && {
    echo "[ COMPILER ] Failed to compile the project"
    exit 1;
} 
echo "[ COMPILER ] Starting the instance"
./${name}.compiled $2 $3
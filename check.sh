#!/bin/bash

for n in {1..100}
do
    # echo "Connection nr $n"
    ./build/bclient 127.0.0.1 1337 "login zaBogdan:P@ssw0rd1" >/dev/null &
done
wait
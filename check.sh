#!/bin/bash

for n in {1..4}
do
    echo "Connection nr $n"
    ./build/bclient 127.0.0.1 1337 $n >/dev/null &
done
wait
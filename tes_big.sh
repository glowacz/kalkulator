#!/bin/bash

gcc -o3 -o wzo kalk.c
g++ -o3 -o gen gen_big.cpp

for i in {1..1}
do
    ./gen > in_big.txt
    ./wzo
    echo "TEST $i   OK"
    #sleep 1s
done
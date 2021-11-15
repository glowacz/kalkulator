#!/bin/bash

gcc -o3 -o wzo kalk.c
g++ -o3 -o bru kalk_cpp.cpp
g++ -o3 -o gen kalk_gen.cpp

for i in {1..100000}
do
    ./gen > in_tes.txt
    #./wzo < kalk.in > wzo.out
    #./bru < kalk.in > bru.out
    ./wzo
    ./bru > bru.out
    diff wzo.out bru.out || break
    echo "TEST $i   OK"
    #sleep 1s
done
#!/bin/bash

gcc -o wzo kalk.c
g++ -o bru kalk_cpp.cpp
g++ -o gen kalk_gen.cpp

for i in {1..100000}
do
    ./gen > kalk.in
    ./wzo < kalk.in > wzo.out
    ./bru < kalk.in > bru.out
    diff wzo.out bru.out || break
    echo "TEST $i   OK"
    #sleep 1s
done
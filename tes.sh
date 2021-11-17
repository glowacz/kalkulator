#!/bin/bash

gcc -o3 -o wzo kalk.c
g++ -o3 -o bru kalk_cpp.cpp
g++ -o3 -o gen gen.cpp

for i in {1..100000}
do
    ./gen > in.txt
    ./wzo
    ./bru > out_bru.txt
    diff -q out.txt out_bru.txt || break
    echo "TEST $i   OK"
    #sleep 1s
done
#!/bin/bash

gcc -o3 -o wzo kalk.c
g++ -o3 -o gen gen_big.cpp

for i in {1..100000}
do
    ./gen > in.txt
    ./wzo
    a=($(wc -l in.txt))
    ln_in=${a[0]}
    op_cnt=$(( ln_in / 5 ))
    ln_out=$(( op_cnt * 7 ))
    ln_out1=($(wc -l out.txt))

    if [ "$ln_out" != "$ln_out1" ]; then
        break
    fi
    if [ -s out.txt ]; then
        echo "TEST $i   OK"
    else
        break
    fi
    #sleep 1s
done
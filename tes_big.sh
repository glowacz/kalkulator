#!/bin/bash

gcc -o3 -o wzo kalk.c
g++ -o3 -o gen gen_big.cpp

for i in {1..100000}
do
    ./gen > in.txt
    
    start_time=$(date +%s.%3N)
    
    ./wzo
    
    end_time=$(date +%s.%3N)
    elapsed=$(echo "scale=3; $end_time - $start_time" | bc)
    
    a=($(wc -l in.txt))
    ln_in=${a[0]}
    op_cnt=$(( ln_in / 7 ))
    ln_out=$(( op_cnt * 8 ))
    ln_out1=($(wc -l out.txt))

    if [ "$ln_out" != "$ln_out1" ]; then
        break
    fi
    if [ -s out.txt ]; then
        echo "TEST $i   OK"
        echo "Time in s: $elapsed"
    else
        break
    fi
    #sleep 1s
done
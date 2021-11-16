#!/bin/bash

a=($(wc -l in_tes.txt))
ln_in=${a[0]}
op_cnt=$(( ln_in / 7 ))
ln_out=$(( op_cnt * 9 ))
ln_out1=($(wc -l bru.out))

echo $ln_in
echo $op_cnt
echo $ln_out
echo $ln_out1

if [ "$ln_out" != "$ln_out1" ]; then
    echo "inne"
else
    echo "rowne"
fi

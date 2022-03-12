#!/bin/bash

rm -f ./perfTestOutput.csv
touch ./perfTestOutput.csv

echo "size,algorithm1,algorithm2" >> ./perfTestOutput.csv
for size in {256..2048..256}
    do
        res1=$(./matrix_math 1 $size | grep "Floating-point ops/sec:" | cut -d" " -f3-)
        res2=$(./matrix_math 2 $size | grep "Floating-point ops/sec:" | cut -d" " -f3-)
        concat=$size$(echo ",")$res1$(echo ",")$res2
        echo $concat >> ./perfTestOutput.csv
    done
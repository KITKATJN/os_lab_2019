#!/bin/bash
rm numbers.txt &> /dev/null
for (( i=1; i <= 150; i++ ))
do
$(od -A n -t d -N 1 /dev/random >> numbers.txt)
done

#! /bin/sh
cat "$@" | awk 'BEGIN { coun=0; sum=0 } { coun++; sum+=$1 } END { print sum/coun }'


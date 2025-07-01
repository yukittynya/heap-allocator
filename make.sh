#!/bin/bash

files=""
for file in "src/"*.c; do
 files+="${file} "
done

gcc -O0 ${files} -o heap
./heap

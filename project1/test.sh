#!/bin/bash

make clean;
make;
currentDate=$(date -u)
filename="./data/"$currentDate."data"
touch "$filename"
echo "INSERT" >> "$filename"
echo "BINARY" >> "$filename"
./bin/project1 insert binary 40000000 >> "$filename"
./bin/project1 insert fibonacci 40000000 >> "$filename"
./bin/project1 insert binary 40000000 >> "$filename"
#!/bin/bash

make clean;
make;
currentDate=$(date -u)
filename="./data/"$currentDate."data"
touch "$filename"

#operations=(2187500 4375000 8750000 17500000 35000000)
operations=(5000000 10000000 15000000 20000000 25000000 30000000 35000000)

# INSERT BINARY
echo "Binary Insert" >> "$filename"
echo "Operations	Seconds	Comparisons" >> "$filename"
for numberOfOperations in ${operations[@]}
do
	./bin/project1 insert binary $numberOfOperations  >> "$filename"
done
echo "" >> "$filename"

# INSERT FIBONACCI
echo "Fibonacci Insert" >> "$filename"
echo "Operations	Seconds	Comparisons" >> "$filename"
for numberOfOperations in ${operations[@]}
do
	./bin/project1 insert fibonacci $numberOfOperations  >> "$filename"
done
echo "" >> "$filename"

# DELETEMIN BINARY
echo "Binary Deletemin" >> "$filename"
echo "Operations	Seconds	Comparisons" >> "$filename"
for numberOfOperations in ${operations[@]}
do
	./bin/project1 deletemin binary $numberOfOperations  >> "$filename"
done
echo "" >> "$filename"

# DELETEMIN FIBONACCI
echo "Fibonacci Deletemin" >> "$filename"
echo "Operations	Seconds	Comparisons" >> "$filename"
for numberOfOperations in ${operations[@]}
do
	./bin/project1 deletemin fibonacci $numberOfOperations  >> "$filename"
done
echo "" >> "$filename"

# DECREASEKEY BINARY
echo "Binary Decreasekey" >> "$filename"
echo "Operations	Seconds	Comparisons" >> "$filename"
for numberOfOperations in ${operations[@]}
do
	./bin/project1 decreasekey binary $numberOfOperations  >> "$filename"
done
echo "" >> "$filename"

# DECREASEKEY FIBONACCI
echo "Fibonacci DecreaseKey" >> "$filename"
echo "Operations	Seconds	Comparisons" >> "$filename"
for numberOfOperations in ${operations[@]}
do
	./bin/project1 decreasekey fibonacci $numberOfOperations  >> "$filename"
done
echo "" >> "$filename"
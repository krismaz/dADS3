#!/bin/bash

make clean;
make;
currentDate=$(date -u)
filename="./data/"$currentDate."data"
touch "$filename"

#operations=(2187500 4375000 8750000 17500000 35000000)
operations=(262144 524288 1048576 2097152 4194304 8388608 16777216)


# PREFIX="valgrind --quiet --tool=massif --pages-as-heap=yes --massif-out-file=massif.out"
# SUFFIX="cat massif.out | grep mem_heap_B | sed -e 's/mem_heap_B=\(.*\)/\1/' | sort -g | tail -n 1"
# SUFFIX='; echo -e "\t" >> "$filename"; #./cat.sh >> "$filename"; echo -e "\n" >> "$filename"'

PREFIX=""

##########
# INSERT #
##########

# VEB
echo "VEB Insert" >> "$filename"
echo "Operations	Seconds	Comparisons" >> "$filename"
for numberOfOperations in ${operations[@]}
do
	$PREFIX ./bin/project2 insert VEB $numberOfOperations >> "$filename"
	#./cat.sh >> "$filename"
done
echo "" >> "$filename"

# BITSMART
echo "bitsmart Insert" >> "$filename"
echo "Operations	Seconds	Comparisons" >> "$filename"
for numberOfOperations in ${operations[@]}
do
	$PREFIX ./bin/project2 insert bitsmart $numberOfOperations $SUFFIX >> "$filename"
	#./cat.sh >> "$filename"
done
echo "" >> "$filename"

# BINARY
echo "binary Insert" >> "$filename"
echo "Operations	Seconds	Comparisons" >> "$filename"
for numberOfOperations in ${operations[@]}
do
	$PREFIX ./bin/project2 insert binary $numberOfOperations $SUFFIX >> "$filename"
	#./cat.sh >> "$filename"
done
echo "" >> "$filename"

# FIBONACCI
echo "fibonacci Insert" >> "$filename"
echo "Operations	Seconds	Comparisons" >> "$filename"
for numberOfOperations in ${operations[@]}
do
	$PREFIX ./bin/project2 insert fibonacci $numberOfOperations $SUFFIX >> "$filename"
	#./cat.sh >> "$filename"
done
echo "" >> "$filename"



#############
# DELETEMIN #
#############

# VEB
echo "VEB Deletemin" >> "$filename"
echo "Operations	Seconds	Comparisons" >> "$filename"
for numberOfOperations in ${operations[@]}
do
	$PREFIX ./bin/project2 deletemin VEB $numberOfOperations  >> "$filename"
	#./cat.sh >> "$filename"
done
echo "" >> "$filename"

# BITSMART
echo "bitsmart Deletemin" >> "$filename"
echo "Operations	Seconds	Comparisons" >> "$filename"
for numberOfOperations in ${operations[@]}
do
	$PREFIX ./bin/project2 deletemin bitsmart $numberOfOperations  >> "$filename"
	#./cat.sh >> "$filename"
done
echo "" >> "$filename"

# BINARY
echo "binary Deletemin" >> "$filename"
echo "Operations	Seconds	Comparisons" >> "$filename"
for numberOfOperations in ${operations[@]}
do
	$PREFIX ./bin/project2 deletemin binary $numberOfOperations  >> "$filename"
	#./cat.sh >> "$filename"
done
echo "" >> "$filename"

# FIBONACCI
echo "fibonacci Deletemin" >> "$filename"
echo "Operations	Seconds	Comparisons" >> "$filename"
for numberOfOperations in ${operations[@]}
do
	$PREFIX ./bin/project2 deletemin fibonacci $numberOfOperations  >> "$filename"
	#./cat.sh >> "$filename"
done
echo "" >> "$filename"







###############
# INTERLEAVED #
###############

# VEB
echo "VEB interleaved" >> "$filename"
echo "Operations	Seconds	Comparisons" >> "$filename"
for numberOfOperations in ${operations[@]}
do
	$PREFIX ./bin/project2 interleaved VEB $numberOfOperations  >> "$filename"
	#./cat.sh >> "$filename"
done
echo "" >> "$filename"

# BITSMART
echo "bitsmart interleaved" >> "$filename"
echo "Operations	Seconds	Comparisons" >> "$filename"
for numberOfOperations in ${operations[@]}
do
	$PREFIX ./bin/project2 interleaved bitsmart $numberOfOperations  >> "$filename"
	#./cat.sh >> "$filename"
done
echo "" >> "$filename"

# BINARY
echo "binary interleaved" >> "$filename"
echo "Operations	Seconds	Comparisons" >> "$filename"
for numberOfOperations in ${operations[@]}
do
	$PREFIX ./bin/project2 interleaved binary $numberOfOperations  >> "$filename"
	#./cat.sh >> "$filename"
done
echo "" >> "$filename"

# FIBONACCI
echo "fibonacci interleaved" >> "$filename"
echo "Operations	Seconds	Comparisons" >> "$filename"
for numberOfOperations in ${operations[@]}
do
	$PREFIX ./bin/project2 interleaved fibonacci $numberOfOperations  >> "$filename"
	#./cat.sh >> "$filename"
done
echo "" >> "$filename"



echo "==================DONE==================" >> "$filename"
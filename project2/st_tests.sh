#!/bin/bash

make clean;
make;
currentDate=$(date -u)
windowsCompatibleCurrentDate=${currentDate//:/;}
filename="./data/"$windowsCompatibleCurrentDate."data"
touch "$filename"

#operations=(2187500 4375000 8750000 17500000 35000000)
operations=(262144 524288 1048576 2097152 4194304 8388608 16777216)


# PREFIX="valgrind --quiet --tool=massif --pages-as-heap=yes --massif-out-file=massif.out"
# SUFFIX="cat massif.out | grep mem_heap_B | sed -e 's/mem_heap_B=\(.*\)/\1/' | sort -g | tail -n 1"
# SUFFIX='; echo -e "\t" >> "$filename"; #./cat.sh >> "$filename"; echo -e "\n" >> "$filename"'

# PREFIX=""

##########
# INSERT #
##########

# VEB
echo "Insert" >> "$filename"
echo "VEB" >> "$filename"
echo "Operations	Seconds	Comparisons" >> "$filename"
for numberOfOperations in ${operations[@]}
do
	./bin/project2 st_insert VEB $numberOfOperations >> "$filename"
	#./cat.sh >> "$filename"
done
echo "" >> "$filename"

# bitsmart
echo "bitsmart" >> "$filename"
echo "Operations	Seconds	Comparisons" >> "$filename"
for numberOfOperations in ${operations[@]}
do
	./bin/project2 st_insert bitsmart $numberOfOperations >> "$filename"
	#./cat.sh >> "$filename"
done
echo "" >> "$filename"

# std::set
echo "std::set" >> "$filename"
echo "Operations	Seconds	Comparisons" >> "$filename"
for numberOfOperations in ${operations[@]}
do
	./bin/project2 st_insert std $numberOfOperations >> "$filename"
	#./cat.sh >> "$filename"
done
echo "" >> "$filename"

#############
# REMOVE #
#############

# VEB
echo "Remove" >> "$filename"
echo "VEB" >> "$filename"
echo "Operations	Seconds	Comparisons" >> "$filename"
for numberOfOperations in ${operations[@]}
do
	./bin/project2 st_remove VEB $numberOfOperations  >> "$filename"
	#./cat.sh >> "$filename"
done
echo "" >> "$filename"

# BITSMART
echo "bitsmart" >> "$filename"
echo "Operations	Seconds	Comparisons" >> "$filename"
for numberOfOperations in ${operations[@]}
do
	./bin/project2 st_remove bitsmart $numberOfOperations  >> "$filename"
	#./cat.sh >> "$filename"
done
echo "" >> "$filename"

# STD::SET
echo "std::set" >> "$filename"
echo "Operations	Seconds	Comparisons" >> "$filename"
for numberOfOperations in ${operations[@]}
do
	./bin/project2 st_remove std $numberOfOperations  >> "$filename"
	#./cat.sh >> "$filename"
done
echo "" >> "$filename"

###############
# PREDECESSOR #
###############

echo "Predecessor" >> "$filename"
# VEB
echo "VEB" >> "$filename"
echo "Operations	Seconds	Comparisons" >> "$filename"
for numberOfOperations in ${operations[@]}
do
	./bin/project2 st_predecessor VEB $numberOfOperations  >> "$filename"
	#./cat.sh >> "$filename"
done
echo "" >> "$filename"

# BITSMART
echo "bitsmart" >> "$filename"
echo "Operations	Seconds	Comparisons" >> "$filename"
for numberOfOperations in ${operations[@]}
do
	./bin/project2 st_predecessor bitsmart $numberOfOperations  >> "$filename"
	#./cat.sh >> "$filename"
done
echo "" >> "$filename"

# STD::SET
echo "std::set" >> "$filename"
echo "Operations	Seconds	Comparisons" >> "$filename"
for numberOfOperations in ${operations[@]}
do
	./bin/project2 st_predecessor std $numberOfOperations  >> "$filename"
	#./cat.sh >> "$filename"
done
echo "" >> "$filename"



###############
# INTERLEAVED #
###############
echo "Interleaved" >> "$filename"
# VEB
echo "VEB" >> "$filename"
echo "Operations	Seconds	Comparisons" >> "$filename"
for numberOfOperations in ${operations[@]}
do
	./bin/project2 st_interleaved VEB $numberOfOperations  >> "$filename"
	#./cat.sh >> "$filename"
done
echo "" >> "$filename"

# BITSMART
echo "bitsmart" >> "$filename"
echo "Operations	Seconds	Comparisons" >> "$filename"
for numberOfOperations in ${operations[@]}
do
	./bin/project2 st_interleaved bitsmart $numberOfOperations  >> "$filename"
	#./cat.sh >> "$filename"
done
echo "" >> "$filename"

# STD::SET
echo "std::set" >> "$filename"
echo "Operations	Seconds	Comparisons" >> "$filename"
for numberOfOperations in ${operations[@]}
do
	./bin/project2 st_interleaved std $numberOfOperations  >> "$filename"
	#./cat.sh >> "$filename"
done
echo "" >> "$filename"



echo "==================DONE==================" >> "$filename"
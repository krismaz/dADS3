#!/bin/bash

make clean;
make;
currentDate=$(date -u)
filename="./data/kris.data"
touch "$filename"
nodes=(1000 2000 3000 4000 5000 6000 7000 8000 9000 10000 11000 12000 13000 14000 15000 16000 17000 18000 19000 20000)

# DIJKSTRA BINARY SIMPLE STRUCTURE	
echo "Binary DIJKSTRA Simple Structure" >> "$filename"
echo "Nodes	Seconds	Comparisons" >> "$filename"
for numberOfNodes in ${nodes[@]}
do
	./bin/profiler.exe dijkstra binary `expr $numberOfNodes \\* 10` 1 >> "$filename"
done
echo "" >> "$filename"

# DIJKSTRA BINARY Complex STRUCTURE	
echo "Binary DIJKSTRA Complex Structure" >> "$filename"
echo "Nodes	Seconds	Comparisons" >> "$filename"
for numberOfNodes in ${nodes[@]}
do
	./bin/profiler.exe dijkstra binary $numberOfNodes 2 >> "$filename"
done
echo "" >> "$filename"

# DIJKSTRA FIBONACCI Simple STRUCTURE	
echo "Fibonacci DIJKSTRA Simple Structure" >> "$filename"
echo "Nodes	Seconds	Comparisons" >> "$filename"
for numberOfNodes in ${nodes[@]}
do
	./bin/profiler.exe dijkstra fibonacci `expr $numberOfNodes \\* 10` 1 >> "$filename"
done
echo "" >> "$filename"

# DIJKSTRA fibonacci Complex STRUCTURE	
echo "fibonacci DIJKSTRA Complex Structure" >> "$filename"
echo "Nodes	Seconds	Comparisons" >> "$filename"
for numberOfNodes in ${nodes[@]}
do
	./bin/profiler.exe dijkstra fibonacci $numberOfNodes 2 >> "$filename"
done
echo "" >> "$filename"

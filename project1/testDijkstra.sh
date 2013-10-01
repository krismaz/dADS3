#!/bin/bash

make clean;
make;
currentDate=$(date -u)
filename="./data/"$currentDate."data"
touch "$filename"
nodes=(5000 10000 15000 16000 17000 18000 19000 20000)

# DIJKSTRA BINARY SIMPLE STRUCTURE	
echo "Binary DIJKSTRA Simple Structure" >> "$filename"
echo "Nodes	Seconds	Comparisons" >> "$filename"
for numberOfNodes in ${nodes[@]}
do
	./bin/project1 dijkstra binary $numberOfNodes 1 >> "$filename"
done
echo "" >> "$filename"

# DIJKSTRA BINARY Complex STRUCTURE	
echo "Binary DIJKSTRA Complex Structure" >> "$filename"
echo "Nodes	Seconds	Comparisons" >> "$filename"
for numberOfNodes in ${nodes[@]}
do
	./bin/project1 dijkstra binary $numberOfNodes 2 >> "$filename"
done
echo "" >> "$filename"

# DIJKSTRA FIBONACCI Simple STRUCTURE	
echo "Fibonacci DIJKSTRA Simple Structure" >> "$filename"
echo "Nodes	Seconds	Comparisons" >> "$filename"
for numberOfNodes in ${nodes[@]}
do
	./bin/project1 dijkstra fibonacci $numberOfNodes 1 >> "$filename"
done
echo "" >> "$filename"

# DIJKSTRA fibonacci Complex STRUCTURE	
echo "fibonacci DIJKSTRA Complex Structure" >> "$filename"
echo "Nodes	Seconds	Comparisons" >> "$filename"
for numberOfNodes in ${nodes[@]}
do
	./bin/project1 dijkstra fibonacci $numberOfNodes 2 >> "$filename"
done
echo "" >> "$filename"

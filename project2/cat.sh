#!/bin/bash
echo "\$"
cat massif.out | grep mem_heap_B | sed -e 's/mem_heap_B=\(.*\)/\1/' | sort -g | tail -n 1

#http://stackoverflow.com/questions/774556/peak-memory-usage-of-a-linux-unix-process
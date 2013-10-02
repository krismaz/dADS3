#!/bin/bash
for file in *.svg 
do
	if test -f "$file"
	then
		output="${file%.svg}.pdf"
		echo converting ["$file"] to [$output]
		rsvg-convert -f pdf -o "$output" "$file"
	fi
done
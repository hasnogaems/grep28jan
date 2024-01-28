#!/bin/bash

# Output file to store the combined content
output_file="combined_output.txt"

# Combine content from target files into the output file
for file in "$@"; do
    if [[ -f "$file" ]]; then
        echo -e "\nContent from file: $file" >> $output_file
        cat "$file" >> $output_file
    fi
done

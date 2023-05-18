#!/bin/bash

i=0
for file in $(ls -1 | grep -oP '.*\d+\.\w+' | sort); do
    input_file="${file%.*}.cpp"
    output_file="${file%.*}.cpp.sal"
    
    if [ -f "$input_file" ]; then
        new_input_file=$(printf "tad%02d.cpp" $i)
        new_output_file=$(printf "tad%02d.cpp.sal" $i)
        
        mv "$input_file" "$new_input_file"
        mv "$output_file" "$new_output_file"
        
        let i++
    fi
done

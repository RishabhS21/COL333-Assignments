#!/bin/bash
input_file="$1"
rish=".satoutput"
final="${input_file}${rish}"
# Run the compiled program with the input file as an argument
./prak2 "$final"

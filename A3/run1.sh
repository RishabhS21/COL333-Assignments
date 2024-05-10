#!/bin/bash

# Extract the input file name from the command line argument
input_file="$1"
rish=".graph"
final="${input_file}${rish}"
# Run the compiled program with the input file as an argument
./prak1 "$final"

#Script for testing codes with generator, brute force code and checker
#Execution:
# ./testing.sh <dir> <code> <brute force> <gen> <checker> 
# <dir> -> The directory where all codes will be found
# <code> -> the code to test
# <brute force> -> the brute force code (already know is correct)
# <gen> -> test generator for the problem
# <checker> -> checks whether the answer given by the <code> is correct
# All parameters are optional except <dir>

#!/bin/bash

#Variables
N=100000 #Maximum number of tests made
dir=$1

code=${2:-$1/code.cpp}
brute=${3:-$1/brute.cpp}
gen=${4:-$1/gen.cpp}
checker=${5:-$1/checker.cpp}

output_dir="$1/output"

#In case of error the script stops
set -e

#Compilation 
g++ $code -o "$output_dir/code"
g++ $brute -o "$output_dir/brute"
g++ $gen -o "$output_dir/gen"
g++ $checker -o "$output_dir/checker"

#Testing
for((i=0;i<N;++i)); do 
    "$output_dir/gen" $i > input_file
    "$output_dir/code" < input_file > myAnswer
    "$output_dir/brute" < input_file > correctAnswer
    "$output_dir/checker" > checker_log
    echo "Passed test: " $i
done

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

out="$1/output"

#In case of error the script stops
set -e

#Compilation 
g++ $code -o "$out/code"
g++ $brute -o "$out/brute"
g++ $gen -o "$out/gen"
g++ $checker -o "$out/checker"

#Testing
for((i=0;i<N;++i)); do 
    "$out/gen" $i > "$out/input_file"
    "$out/code" < "$out/input_file" > "$out/myAnswer"
    "$out/brute" < "$out/input_file" > "$out/correctAnswer"
    "$out/checker" > "$out/checker_log"
    echo "Passed test: " $i
done

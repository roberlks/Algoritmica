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

if (($# < 1)) 
then
    echo "./testing.sh <dir> <code> <brute force> <gen> <checker> "
    echo "<dir>          The directory where all codes will be found"
    echo "<code>         the code to test"
    echo "<brute force>  the brute force code (already know is correct)"
    echo "<gen>          test generator for the problem"
    echo "<checker>      checks whether the answer given by the <code> is correct"
    echo "All parameters are optional except <dir>"
    exit 1
fi;

#Variables
N=100000 #Maximum number of tests made
dir=$1

code=${2:-$1/code.cpp}
brute=${3:-$1/brute.cpp}
gen=${4:-$1/gen.cpp}
checker=${5:-$1/checker.cpp}

output_dir="$1/output"
mkdir -p $output_dir

input="$output_dir/input_file"
my_ans="$output_dir/myAnswer"
correct_ans="$output_dir/correctAnswer"
log="$output_dir/checker_log"

#In case of error the script stops
set -e

#Compilation 
g++ $code -o "$output_dir/code" 
g++ $brute -o "$output_dir/brute" 
g++ $gen -o "$output_dir/gen" 
g++ $checker -o "$output_dir/checker" 

echo "" > $my_ans

#Testing
for((i=0;i<N;++i)); do 
    "$output_dir/gen" $i > $input
    "$output_dir/code" < $input >> $my_ans
    echo "Passed test: " $i
done

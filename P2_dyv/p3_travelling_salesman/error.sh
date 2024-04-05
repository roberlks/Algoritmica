#!/bin/bash

if (($# < 1)) 
then
    echo "./error.sh <dir> <code> <brute force> <gen> <checker> "
    echo "<dir>          The directory where all codes will be found"
    echo "<code>         the code to test"
    echo "<brute force>  the brute force code (already know is correct)"
    echo "<gen>          test generator for the problem"
    echo "All parameters are optional except <dir>"
    exit 1
fi;

#Variables
N=10 #Maximum number of tests made
dir=$1

code=${2:-$1/code.cpp}
brute=${3:-$1/brute.cpp}
gen=${4:-$1/gen.cpp}
error="$1/error.cpp"

output_dir="$1/output"
mkdir -p $output_dir

input="$output_dir/input_file"
my_ans="$output_dir/myAnswer"
correct_ans="$output_dir/correctAnswer"
log="$output_dir/error_log"


#In case of error the script stops
set -e

#Compilation 
g++ $code -o "$output_dir/code" 
g++ $brute -o "$output_dir/brute" 
g++ $gen -o "$output_dir/gen" 
g++ $error -o "$output_dir/error" 

sum=0.0
local=0.0
#Testing
for((i=0;i<N;++i)); do 
    "$output_dir/gen" $i > $input
    "$output_dir/code" < $input > $my_ans
    "$output_dir/brute" < $input > $correct_ans
    "$output_dir/error" "$input" "$my_ans" "$correct_ans" > $log
    if [[ $(head -c 2 $log) == "WA" ]]; then
        echo $log
        exit 1
    fi
    local=$(head -1 $log)
    echo "Test "$i": "$local"%"
    sum=$(awk "BEGIN {printf \"%.2f\", $sum + $local}")
done

average=$(awk "BEGIN {printf \"%.6f\", $sum / $N}")

echo "Average error: " $average

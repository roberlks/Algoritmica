#Script that given the directory with the inputs, run each input with the code 
#Execution:
# ./test.sh <dirInput> <dirCode> <code> 
# <dirInput> -> The directory where all the inputs will be found
# <dirCode>-> The directory where the code is
# <code> -> the code to test
# <sufix> -> sufix that the code will have 
#!/bin/bash

if (($# < 1)) 
then
    echo "./test.sh <dirInput> <dirCode> <code>  <sufix>"
    echo "<dirInput> -> The directory where all the inputs will be found"
    echo "<dirCode> -> The directory where the code is"
    echo "<code> -> the code to test"
    echo "<sufix> -> the sufix of the result (optional)"
    exit 1
fi;

#Variables
input_dir=$1
code=${3:-$2/code.cpp}
sufix=$4

output_dir="$2/output"
mkdir -p $output_dir

input="$output_dir"
results="$output_dir/testing_results${sufix}"
log="$output_dir/checker_log"

#In case of error the script stops
set -e

#Compilation 
g++ $code -o "$output_dir/code" -D OBTENER_TIEMPOS

echo "" > $results
echo "" > $log

#Testing
for filename in $input_dir/in*.txt
do  
    echo "Fichero input $filename" >> $log
    echo "Contenido fichero: " >> $log
    head $filename >> $log
    echo "" >> $log

    "$output_dir/code" < $filename >> $results
done

aux=aux.txt
touch $aux
sort -n -k 1 $results > $aux
cat $aux > $results
rm $aux

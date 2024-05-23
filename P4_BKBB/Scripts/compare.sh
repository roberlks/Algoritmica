#!/bin/bash

if (($# < 5)); then
    echo "Error: missing paremeters"
    echo "IMPORTANTE: Ejecutar desde la carpeta padre"
    echo "$0 <BK/BB> <ini> <fin> <step> [version]"
    echo "<BK/BB>: main folder of the problem"
    echo "<ini> initial size of the output to generate"
    echo "<fin> final size of the output to generate"
    echo "<step> incremental size of the output to generate"
    echo "<version1> f_cota version 1 (the good one)" 
    echo "<version2> f_cota version 2 (the tested one)"
    exit -1;
fi

ini=$2
fin=$3
step=$4
version1=$5
version2=$6

./Scripts/input_generator.sh $1 $ini $fin $step

cd $1

greedy="Algoritmo/algoritmo_cost"
instances_dir="Instancias"

make cost
error=0
for((i=ini; i<=fin; i+=step)); do
    let index=i-ini
    let index=index/step
    let ++index
    instance="ni$index.txt"
    expected=$("$greedy" "$instances_dir/$instance" $version1)
    got=$("$greedy" "$instances_dir/$instance" $version2)
    failed=$(echo "$num1 -ne $num2" | bc)
    if [ "$failed" -eq 1 ]
    then
        echo "Error: WA in instance $instance"
        break
    fi
done
echo "Equal results"
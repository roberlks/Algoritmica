#!/bin/bash

if (($# < 4)); then
    echo "Error: missing paremeters"
    echo "$0 <P[1..3]> <ini> <fin> <step>"
    echo "<P[1..3]>: main folder of the problem"
    echo "<ini> initial size of the output to generate"
    echo "<fin> final size of the output to generate"
    echo "<step> incremental size of the output to generate"
    exit -1;
fi

ini=$2
fin=$3
step=$4

gen="$1/Generador/generador"
output_dir="$1/Instancias"
makefile="$1/Makefile"

mkdir -p $output_dir

make -f $makefile $gen

for((i=ini; i<=fin; i+=step)); do
    let index=i-ini
    let index=index/step
    let ++index
    output_name="in$index.txt"
    ./$gen $i "$output_dir/$output_name"
done
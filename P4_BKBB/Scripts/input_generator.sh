#!/bin/bash

if (($# < 4)); then
    echo "Error: missing paremeters"
    echo "$0 <BK/BB> <ini> <fin> <step>"
    echo "<BK/BB>: main folder of the problem"
    echo "<ini> initial size of the output to generate"
    echo "<fin> final size of the output to generate"
    echo "<step> incremental size of the output to generate"
    exit -1;
fi

ini=$2
fin=$3
step=$4

cd $1

gen="Generador/generador"
output_dir="Instancias"
makefile="Makefile"

mkdir -p $output_dir

make -f $makefile $gen

for((i=ini; i<=fin; i+=step)); do
    let index=i-ini
    let index=index/step
    let ++index
    output_name="ni$index.txt"
    ./$gen $i "$output_dir/$output_name"
done
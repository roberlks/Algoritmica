#!/bin/bash

if (($# < 4)); then
    echo "Error: missing paremeters"
    echo "$0 <P[1..3]> <ini> <fin> <step> <dyv/especifico>"
    echo "<P[1..3]>: main folder of the problem"
    echo "<ini> initial size of the output to generate"
    echo "<fin> final size of the output to generate"
    echo "<step> incremental size of the output to generate"
    echo "<dyv/especifico> algorithm to take time"
    exit 1
fi

ini=$2
fin=$3
step=$4

if [[ $5 == "dyv" ]]; then
    alg="$1/DyV/dyv"
    output_dir="$1/DyV"
elif [[ $5 == "especifico" ]]; then 
        alg="$1/Especifico/especifico"
        output_dir="$1/Especifico"
else
    echo "Error: invalid arguments"
    echo "$0 <P[1..3]> <ini> <fin> <step> <dyv/especifico>"
    echo "<P[1..3]>: main folder of the problem"
    echo "<ini> initial size of the output to generate"
    echo "<fin> final size of the output to generate"
    echo "<step> incremental size of the output to generate"
    echo "<dyv/especifico> algorithm to take time"
    exit 1
fi
input_dir="$1/Instancias"
makefile="$1/Makefile"
output_name="times.dat"

mkdir -p $output_dir

echo " " > "$output_dir/$output_name"

make -f $makefile $alg

for((i=ini; i<=fin; i+=step)); do
    let index=i-ini
    let index=index/step
    let ++index
    input_name="in$index.txt"
    cat "$input_dir/$input_name" | "$alg" >> "$output_dir/$output_name"
done
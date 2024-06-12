#!/bin/bash

if (($# < 5)); then
    echo "Error: missing paremeters"
    echo "IMPORTANTE: Ejecutar desde la carpeta padre"
    echo "$0 <BK/BB> <ini> <fin> <step> <version>"
    echo "<BK/BB>: main folder of the problem"
    echo "<ini> initial size of the output to generate"
    echo "<fin> final size of the output to generate"
    echo "<step> incremental size of the output to generate"
    echo "<version> f_cota version"
    exit -1;
fi

ini=$2
fin=$3
step=$4
version=$5

./Scripts/input_generator.sh $1 $ini $fin $step

cd $1

greedy="Algoritmo/algoritmo_nodes"
instances_dir="Instancias"
make nodes

for((i=ini; i<=fin; i+=step)); do
    let index=i-ini
    let index=index/step
    let ++index
    instance="ni$index.txt"
    input_name="ni$index.dat"
    echo "Cities: $i"
    "$greedy" "$instances_dir/$instance" "$version"
done

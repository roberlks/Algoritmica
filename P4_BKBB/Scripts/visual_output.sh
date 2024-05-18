#!/bin/bash

if (($# < 4)); then
    echo "Error: missing paremeters"
    echo "IMPORTANTE: Ejecutar desde la carpeta padre"
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

path_mode="linespoints"
graph_mode="points"


./Scripts/input_generator.sh $1 $ini $fin $step
./Scripts/visual_input_generator.sh $1 $ini $fin $step

cd $1

greedy="Algoritmo/tsp3"
instances_dir="Instancias"
data_input_dir="Visual/Data/Input"
data_output_dir="Visual/Data/Output"
graph_output_dir="Visual/Graph/Output"
makefile="Makefile"
plot_script="../Scripts/plot_path.gp"

mkdir -p $data_output_dir
mkdir -p $graph_output_dir
g++ Algoritmo/TSP3.cpp -o Algoritmo/tsp3

make -f $makefile $greedy

for((i=ini; i<=fin; i+=step)); do
    let index=i-ini
    let index=index/step
    let ++index
    instance="ni$index.txt"
    input_name="ni$index.dat"
    output_name="out$index.dat"
    image_name="path$index.png"
    "$greedy" "$instances_dir/$instance" > "$data_output_dir/$output_name"
    gnuplot -c $plot_script "$data_input_dir/$input_name" "$data_output_dir/$output_name" "Graph" "Path" "$graph_mode" "$path_mode" "$graph_output_dir/$image_name" 
done

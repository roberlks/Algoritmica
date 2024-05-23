#!/bin/bash

if (($# < 5)); then
    echo "Error: missing paremeters"
    echo "IMPORTANTE: Ejecutar desde la carpeta padre"
    echo "$0 <BK/BB> <ini> <fin> <step> [version]"
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

path_mode="linespoints"
graph_mode="points"


./Scripts/input_generator.sh $1 $ini $fin $step 

cd $1

greedy="Algoritmo/algoritmo_nodes"
instances_dir="Instancias"
data_input_dir="Nodes/Data/Input"
data_output_dir="Nodes/Data/Output"
graph_output_dir="Nodes/Graphs/Output"
output_name="out.dat"
makefile="Makefile"
plot_script="../Scripts/gnuplot_graficas.gp"

mkdir -p $data_output_dir
mkdir -p $graph_output_dir

make nodes

echo " " > "$data_output_dir/$output_name"
for((i=ini; i<=fin; i+=step)); do
    let index=i-ini
    let index=index/step
    let ++index
    instance="ni$index.txt"
    echo "Instance: $i"
    "$greedy" "$instances_dir/$instance" $version >> "$data_output_dir/$output_name"
done

cat "$data_output_dir/$output_name"

gnuplot -c $plot_script "2" "$data_output_dir/$output_name" "$version"

echo "Stored regresions in $1/$data_output_dir"
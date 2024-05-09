#!/bin/bash

export LC_NUMERIC="en_US.UTF-8"

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
mode="linespoints"

if [[ $1 == "P4" ]]; then
    mode="points"
fi

cd $1

gen="Generador/visual_generator"
data_output_dir="Visual/Data/Input"
graph_output_dir="Visual/Graph/Input"
makefile="Makefile"
plot_script="../Scripts/plot_graph.gp"

mkdir -p $data_output_dir
mkdir -p $graph_output_dir

make -f $makefile $gen

for((i=ini; i<=fin; i+=step)); do
    let index=i-ini
    let index=index/step
    let ++index
    data_name="ni$index.dat"
    ./$gen $i "$data_output_dir/$data_name"
    graph_name="graph$index.png"
    gnuplot -c $plot_script "$data_output_dir/$data_name" "Graph" "$graph_output_dir/$graph_name" "$mode"
done
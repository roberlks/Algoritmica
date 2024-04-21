#!/bin/bash

if (($# < 4)); then
    echo "Error: missing paremeters"
    echo "$0 <P[1..4]> <ini> <fin> <step> [<version>]"
    echo "<P[1..4]>: main folder of the problem"
    echo "<ini> initial size of the output to generate"
    echo "<fin> final size of the output to generate"
    echo "<step> incremental size of the output to generate"
    exit -1;
fi

ini=$2
fin=$3
step=$4

path_mode="linespoints"
graph_mode="linespoints"

if [[ $1 == "P4" ]]; then
    graph_mode="points"

    if (($# < 5)); then
        echo "Please especify version of TSP:"
        echo "$0 <P[1..4]> <ini> <fin> <step> [1..3]"
        exit -1
    fi
    version=V$5
fi


./Scripts/input_generator.sh $1 $ini $fin $step
./Scripts/visual_input_generator.sh $1 $ini $fin $step

cd $1

echo "VERSION: $version"

greedy="Greedy/$version/greedy"
instances_dir="Instancias"
data_input_dir="Visual/Data/Input"
data_output_dir="Visual/Data/Output"
graph_output_dir="Visual/Graph/Output"
makefile="Makefile"
plot_script="../Scripts/plot_path.gp"

mkdir -p $data_output_dir
mkdir -p $graph_output_dir

make -f $makefile $greedy

for((i=ini; i<=fin; i+=step)); do
    let index=i-ini
    let index=index/step
    let ++index
    instance="ni$index.txt"
    input_name="in$index.dat"
    output_name="out$index.dat"
    image_name="path$index.png"
    "$greedy" "$instances_dir/$instance" > "$data_output_dir/$output_name"
    gnuplot -c $plot_script "$data_input_dir/$input_name" "$data_output_dir/$output_name" "Graph" "Path" "$graph_mode" "$path_mode" "$graph_output_dir/$image_name" 
done

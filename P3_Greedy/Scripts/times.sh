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

version="."

if [[ $1 == "P4" ]]; then

    if (($# < 5)); then
        echo "Please especify version of TSP:"
        echo "$0 <P[1..4]> <ini> <fin> <step> [1..3]"
        exit -1
    fi
    version=V$5
fi

./Scripts/input_generator.sh $1 $ini $fin $step

cd $1

greedy="Greedy/$version/greedy_time"
instances_dir="Instancias"
data_output_dir="Times/$version/Data"
graph_output_dir="Times/$version/Graph"
log_dir="Times/$version/Log"
image_name="times$1.png"
regresion_image="regresion_cuadratica$1.png"
output_name="times$1.dat"
log_name="log_cuadratico"
makefile="Makefile"
plot_script="../Scripts/g1.gp"
regresion_script="../Scripts/regresion.gp"

mkdir -p $instances_dir
mkdir -p $data_output_dir
mkdir -p $graph_output_dir
mkdir -p $log_dir

make -f $makefile $greedy "time"

echo " " > "$data_output_dir/$output_name"
for((i=ini; i<=fin; i+=step)); do
    let index=i-ini
    let index=index/step
    let ++index
    instance="ni$index.txt"
    "$greedy" "$instances_dir/$instance" >> "$data_output_dir/$output_name"
    
done

gnuplot -c $plot_script "$data_output_dir/$output_name" "Eficiencia $1" "Nº ciudades" "$graph_output_dir/$image_name" "linespoints"
gnuplot -c $regresion_script "$data_output_dir/$output_name" "Eficiencia $1" "Nº ciudades" "$graph_output_dir/$regresion_image" "$log_dir/$log_name"

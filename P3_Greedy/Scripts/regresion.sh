#!/bin/bash

cd $1

greedy="Greedy/$version/greedy"
instances_dir="Instancias"
data_output_dir="Times/Data"
graph_output_dir="Times/Graph"
image_name="regresion$1.png"
output_name="regresion$1.dat"
log_dir="Times/Log"
log_name="log_cuadratico"
makefile="Makefile"
plot_script="../Scripts/g1.gp"

mkdir -p $data_output_dir
mkdir -p $graph_output_dir
mkdir -p $log_dir

make -f $makefile $greedy

echo " " > "$data_output_dir/$output_name"
for((i=ini; i<=fin; i+=step)); do
    let index=i-ini
    let index=index/step
    let ++index
    instance="ni$index.txt"
    "$greedy" "$instances_dir/$instance" >> "$data_output_dir/$output_name"
    
done

gnuplot -c $plot_script "$data_output_dir/$output_name" "Eficiencia $1" "Nº ciudades" "$graph_output_dir/$image_name" "linespoints"
#!/bin/bash
# ./testing.sh <exec> <ini> <fin> <step> <data>

data_path="../Datos/$1_data"
exec_path="../codigos/output"
graph_path="../Graficas/$1"

mkdir -p $exec_path
mkdir -p $data_path

data="$data_path/$1_${5:-$USER}.dat" 

exec="$exec_path/$1"
ini=$2
fin=$3
step=$4

g++ "../codigos/$1.cpp" -o "$exec_path/$1"

echo "" > $data

for (( i=ini; i <= fin; i=i + step ))
do
    echo "$i" > "tmp"
    ./$exec $i < "tmp" >> $data 
done

rm "tmp"

# Llamar script de gnuplot para generar las graficas 

scriptgnuplot="g1.gp"

gnuplot -c $scriptgnuplot $data "Eficiencia $1" "Tamaño entrada" "${graph_path}Puntos.jpeg" "2"
gnuplot -c $scriptgnuplot $data "Eficiencia $1" "Tamaño entrada" "${graph_path}Lineas.jpeg" "1"

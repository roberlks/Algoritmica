#!/bin/bash
# ./testing.sh <exec> <ini> <fin> <step> <data>

data_path="../Datos"
exec_path="../codigos/output"
graph_path="../Graficas/$1"

data="$data_path/$1_${5:-$USER}.dat" 

exec="$exec_path/$1"
ini=$2
fin=$3
step=$4

echo "" > $data

for (( i=ini; i < fin; i=i + step ))
do
    echo "$i" > "tmp"
    ./$exec $i < "tmp" >> $data 
done

rm "tmp"

# Llamar script de gnuplot para generar las graficas 

scriptgnuplot="g1.gp"

gnuplot -c $scriptgnuplot $data "Eficiencia $1" "Tamaño datos" "${graph_path}Puntos.jpeg" "2"
gnuplot -c $scriptgnuplot $data "Eficiencia $1" "Tamaño datos" "${graph_path}Lineas.jpeg" "1"

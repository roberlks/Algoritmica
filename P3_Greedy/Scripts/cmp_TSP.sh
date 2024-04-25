#!/bin/bash

rm -rf "../P4/Instancias"

./input_generator.sh ../P4 100 1000 100 

cd ../P4

make -f "Makefile" "time"

mkdir -p Graficas/Data/V{1..3}

for i in $(seq 2 3) 
do
    echo "" > "Graficas/Data/V$i/time.dat"
done

for((i=1;i<=10;++i))
do
    for j in $(seq 2 3) 
    do
        ./Greedy/"V$j"/greedy_time "Instancias/ni$i.txt" >> "Graficas/Data/V$j/time.dat"
    done
done

gnuplot -c "../Scripts/gnuplot_TAM_VARIABLE.gp" "Graficas/Data/V2/time.dat Graficas/Data/V3/time.dat" "V2 V3" "Graficas/TSP_eficiencia.png" "Num ciudades (n)" "Tiempo (seg)"

make cost


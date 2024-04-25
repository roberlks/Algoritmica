#!/bin/bash

rm -rf "../P4/Instancias"

./input_generator.sh ../P4 10 100 10

cd ../P4

make -f "Makefile" "time"

mkdir -p "Graficas/Data"

for i in $(seq 1 3) 
do
    echo "" > "Graficas/Data/time_V$i.dat"
done

for((i=1;i<=10;++i))
do
    for j in $(seq 1 3) 
    do
        ./Greedy/"V$j"/greedy_time "Instancias/ni$i.txt" >> "Graficas/Data/time_V$j.dat"
    done
done

gnuplot -c "../Scripts/gnuplot_TAM_VARIABLE.gp" "Graficas/Data/time_V1.dat Graficas/Data/time_V2.dat Graficas/Data/time_V3.dat" "V1 V2 V3" "Graficas/TSP_eficiencia.png" "Num ciudades (n)" "Tiempo (seg)"

make cost

mkdir -p "Graficas/Data"

for i in $(seq 1 3) 
do
    echo "" > "Graficas/Data/cost_V$i.dat"
done

for((i=1;i<=10;++i))
do
    for j in $(seq 1 3) 
    do
        ./Greedy/"V$j"/greedy_cost "Instancias/ni$i.txt" >> "Graficas/Data/cost_V$j.dat"
    done
done

gnuplot -c "../Scripts/gnuplot_TAM_VARIABLE.gp" "Graficas/Data/cost_V1.dat Graficas/Data/cost_V2.dat Graficas/Data/cost_V3.dat" "V1 V2 V3" "Graficas/TSP_calidad.png" "Num ciudades (n)" "Costo ciclo min"


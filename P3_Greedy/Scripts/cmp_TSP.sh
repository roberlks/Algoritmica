#!/bin/bash

rm -rf "../P4/Instancias"

ini_input=100
fin_input=1000
step=100

./input_generator.sh ../P4 $ini_input $fin_input $step

cd ../P4

make -f "Makefile" "time"

mkdir -p "Graficas/Data"

v_ini=1
v_fin=3

for i in $(seq $v_ini $v_fin)  
do
    echo "" > "Graficas/Data/time_V$i.dat"
done

for((i=1;i<=10;++i))
do
    for j in $(seq $v_ini $v_fin)  
    do
        ./Greedy/"V$j"/greedy_time "Instancias/ni$i.txt" >> "Graficas/Data/time_V$j.dat"
    done
done

gnuplot -c "../Scripts/gnuplot_TAM_VARIABLE.gp" "Graficas/Data/time_V1.dat Graficas/Data/time_V2.dat Graficas/Data/time_V3.dat" "V1 V2 V3" "Graficas/TSP_eficiencia.png" "Num ciudades (n)" "Tiempo (seg)"

make cost

mkdir -p "Graficas/Data"

for i in $(seq $v_ini $v_fin)   
do
    echo "" > "Graficas/Data/cost_V$i.dat"
done

for((i=1;i<=10;++i))
do
    for j in $(seq $v_ini $v_fin)   
    do
        ./Greedy/"V$j"/greedy_cost "Instancias/ni$i.txt" >> "Graficas/Data/cost_V$j.dat"
    done
done

gnuplot -c "../Scripts/gnuplot_TAM_VARIABLE.gp" "Graficas/Data/cost_V1.dat Graficas/Data/cost_V2.dat Graficas/Data/cost_V3.dat" "V1 V2 V3" "Graficas/TSP_calidad.png" "Num ciudades (n)" "Costo ciclo min"


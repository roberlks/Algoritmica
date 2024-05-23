#!/bin/bash
#TODO adaptar
#<P4> <V2>
if (($# < 1)); then
    echo "IMPORTANTE: Ejecutar desde la carpeta padre"
    echo "<BK/BB> [ini] [fin] [step]"
    exit -1
fi

alg=$1
ini=${2:-10}
fin=${3:-100}
step=${4:-10}

./Scripts/input_generator.sh $alg $ini $fin $step

cd $alg

bin="Algoritmo/algoritmo_time"

make time
mkdir -p "Graficas/Data"
output_file="Graficas/Data/time.dat"
echo "" > $output_file
for ((i=1;i<=(fin-ini)/step;++i))
do
    data_name="Instancias/ni$i.txt"
    ./$bin $data_name >> $output_file
done

gnuplot -c "../Scripts/plot.gp" $output_file "tiempo $alg" "Graficas/TSP_$1_empirica_lines.png" "lines"
gnuplot -c "../Scripts/plot.gp" $output_file "tiempo $alg" "Graficas/TSP_$1_empirica_points.png" "points"

gnuplot -c "../Scripts/gnuplot_graficas2.gp" "1" $output_file "tiempo $alg" 
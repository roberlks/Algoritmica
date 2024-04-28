#!/bin/bash
#<P4> <V2>
if (($# < 1)); then
    echo "<V> [ini] [fin] [step]"
    exit -1
fi

ini=${2:-10}
fin=${3:-100}
step=${4:-10}

./Scripts/input_generator.sh "./P4" $ini $fin $step

bin="P4/Greedy/V$1/greedy_time"

make -f "P4/Makefile" $bin
mkdir -p "P4/Graficas/Data"
output_file="P4/Graficas/Data/time.dat"
echo "" > $output_file
for ((i=1;i<=(fin-ini)/step;++i))
do
    data_name="P4/Instancias/ni$i.txt"
    ./$bin $data_name >> $output_file
done

gnuplot -c "./Scripts/plot.gp" $output_file "tiempo greedy v2" "P4/Graficas/TSP_V$1_empirica_lines.png" "lines"
gnuplot -c "./Scripts/plot.gp" $output_file "tiempo greedy v2" "P4/Graficas/TSP_V$1_empirica_points.png" "points"

gnuplot -c "./Scripts/gnuplot_graficas.gp" "1" $output_file "tiempo greedy v2" 
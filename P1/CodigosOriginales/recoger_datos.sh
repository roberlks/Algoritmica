#!/bin/bash

#Objetivo: mirar el tiempo que tarda en ejecutarse un algoritmo 
#según el tamaño de entrada. 
#El tamaño de los datos varían desde <inicial> hasta <final> con saltos de <saltos>

# Argumentos: <algoritmo.exe> <inicial> <final> <saltos> <fich_salida>

programa=$1
inicial=$2
final=$3
saltos=$4
nombre_salida="${programa}_$5.dat"

# Crear fichero de datos

echo " " > $nombre_salida
for (( i=inicial; i < final; i=i + saltos ))
do 

	./$programa $i >> $nombre_salida
done

# Llamar script de gnuplot para generar las graficas 

scriptgnuplot="g1.gp"

gnuplot -c $scriptgnuplot $nombre_salida "Eficiencia" "Tamaño datos" "${programa}Puntos.jpeg" "2"
gnuplot -c $scriptgnuplot $nombre_salida "Eficiencia" "Tamaño datos" "${programa}Lineas.jpeg" "1"



#!/bin/bash

#Objetivo: mirar el tiempo que tarda en ejecutarse un algoritmo según el tamaño de entrada. El tamaño de los datos varían desde <inicial> hasta <final> con saltos de <saltos>

# Argumentos: <algoritmo> <tipo> <inicial> <final> <saltos>

algoritmo=$1
tipo=$2
inicial=$3
final=$4
saltos=$5
programa="${algoritmo}_${tipo}"
datapath="../Datos/${algoritmo}_data/${programa}"

# Crear fichero de datos

echo " " > "${datapath}.dat"
for (( i= inicial; i <= final; i = i + saltos ))
do 
	../ejecutables/$programa $i >> "${datapath}.dat"
done

# Llamar script de gnuplot para generar las graficas 

scriptgnuplot="g1.gp"

gnuplot -c $scriptgnuplot "${datapath}.dat" "Eficiencia ${algoritmo}" "Tamaño datos" "${datapath}_puntos.png" "2"
gnuplot -c $scriptgnuplot "${datapath}.dat" "Eficiencia ${algoritmo}" "Tamaño datos" "${datapath}_lineas.png" "1"



#!/bin/gnuplot

# Obtiene las regresiones para los algoritmos de ordenación dado el algoritmo, el tipo de dato y el tipo de regresión, aunque para esto último hay que modificar la f
# Forma de uso: gnuplot -c regresion_ordenacion.gp <algoritmo> <tipo_dato> <tipo_regresión> 


ALG=ARG1
TYPE=ARG2
REG=ARG3
TITLE="Regresión ".ALG
DATAPATH="../Datos/".ALG."_data/dats/"
NOMBRE_IMAGEN=REG."_".ALG."_".TYPE.".png"
DATOS=DATAPATH.ALG."_".TYPE.".dat"

set terminal png
set output DATAPATH."/../graphs/".NOMBRE_IMAGEN
set fit logfile DATAPATH.ALG."_".TYPE."_".REG.".log"

set xlabel "Tamaño"
set ylabel "Tiempo (seg)"

f(x)=a*x*x # Cambiar para cambiar el tipo de regresión

fit f(x) DATOS via a # Cambiar si se necesitan más parámetros

plot DATOS title TITLE with points, \
	 f(x) title "Curva ajustada"



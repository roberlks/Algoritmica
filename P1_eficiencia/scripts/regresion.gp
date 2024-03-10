#!/bin/gnuplot

# Obtiene las graficas dados los argumentos
# Forma de uso: gnuplot <algoritmo> <tipo_regresion>


ALG=ARG1
TYPE=ARG2
TITLE="Regresión ".ALG
DATAPATH="../Datos/".ALG."_data/"
NOMBRE_IMAGEN=ALG."_".TYPE.".png"
DATOS=ALG."_".TYPE.".dat"

set terminal png
set output DATAPATH."graphs/".NOMBRE_IMAGEN
set fit logfile DATAPATH.ALG."_".TYPE.".log"

set xlabel "Tamaño"
set ylabel "Tiempo (seg)"

# Cambiar para cambiar ajuste
f(x)=a**x		

# Cambiar si se van a usar más parámetros
fit f(x) DATOS via a

plot DATOS title TITLE with points, \
	 f(x) title "Curva ajustada"



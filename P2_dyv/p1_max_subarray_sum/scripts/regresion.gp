#!/bin/gnuplot

# Obtiene las graficas dados los argumentos
# Forma de uso: gnuplot <titulo>


TITLE=ARG1
DATAPATH="./"
NOMBRE_IMAGEN="regresion.png"
DATOS=DATAPATH."times.dat"

set terminal png
set output DATAPATH.NOMBRE_IMAGEN
set fit logfile DATAPATH."regresion.log"

set xlabel "Tamaño(n)"
set ylabel "Tiempo (seg)"

# Cambiar para cambiar ajuste
f(x)=a*x

# Cambiar si se van a usar más parámetros
fit f(x) DATOS via a

plot DATOS title TITLE with points, \
	f(x) title "Curva ajustada"

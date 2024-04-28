#!/bin/gnuplot

# Obtiene las graficas dados los argumentos
# Forma de uso: gnuplot <datos> <titulo> <xlabel> <imagen> <log> 

DATOS=ARG1
TITLE=ARG2
XLABEL=ARG3
IMG=ARG4
LOG=ARG5


set terminal png
set output IMG
set fit logfile LOG

set xlabel XLABEL
set ylabel "Tiempo (seg)"

# Cambiar para cambiar ajuste
f(x)=a*x*log(x)

# Cambiar si se van a usar más parámetros
fit f(x) DATOS via a

plot DATOS title TITLE with points, \
	 f(x) title "Ajuste"



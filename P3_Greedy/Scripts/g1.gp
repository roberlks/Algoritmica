#!/bin/gnuplot

# Obtiene las graficas dados los argumentos
# Forma de uso: gnuplot <nombre_fichero_datos> <titulo de la grafica> <etiqueta_x> <nombre_salida.png>


DATO=ARG1
TITLE=ARG2
ETIQUETA_X=ARG3
NOMBRE_IMAGEN=ARG4
MODE=ARG5

set terminal png
set output NOMBRE_IMAGEN

set xlabel ETIQUETA_X
set ylabel "Tiempo (seg)"
	
plot DATO title TITLE with @MODE

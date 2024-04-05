#!/bin/gnuplot

# Obtiene las graficas dados los argumentos
# Forma de uso: gnuplot <nombre_fichero_datos> <titulo de la grafica> <etiqueta_x> <nombre_salida.jpeg>
#			 <1 o 2>


DATO=ARG1
TITLE=ARG2
ETIQUETA_X=ARG3
NOMBRE_IMAGEN=ARG4

set terminal jpeg
set output NOMBRE_IMAGEN

set xlabel ETIQUETA_X
set ylabel "Tiempo (seg)"

if ( ARG5 == 1) {
	plot DATO title TITLE with lines
}
else {

	plot DATO title TITLE with points
}

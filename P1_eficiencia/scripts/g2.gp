#!/bin/gnuplot

# Obtiene las graficas dados los argumentos
# Forma de uso: gnuplot <nombre_algoritmo> <titulo de la grafica> <nombre_salida.png>
#			 <1 o 2>

ALG=ARG1
DATAPATH="../data/".ALG."_data"
NOMBRE_IMAGEN=ARG2

set terminal png
set output DATAPATH."/graphs/".NOMBRE_IMAGEN

set xlabel "Tamaño datos"
set ylabel "Tiempo (seg)"

if ( ARG3 == 1) {
	plot DATAPATH."/".ALG."_int.dat" title "int" with lines, \
		 DATAPATH."/".ALG."_float.dat" title "float" with lines, \
		 DATAPATH."/".ALG."_double.dat" title "double" with lines, \
		 DATAPATH."/".ALG."_string.dat" title "string" with lines
}
else {
	plot DATAPATH."/".ALG."_int.dat" title "int" with points, \
		 DATAPATH."/".ALG."_float.dat" title "float" with points, \
		 DATAPATH."/".ALG."_double.dat" title "double" with points, \
		 DATAPATH."/".ALG."_string.dat" title "string" with points
}

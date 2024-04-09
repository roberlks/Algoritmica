#!/bin/gnuplot

# <numero de entradas> <datos1> <datos2> <nombre_datos1> <nombre_datos2>

decision=ARG1   	# Si numero de entradas es == 1 entonces solo hace regresion, si es 2 hace la comparacion

datos1=ARG2
datos2=ARG3

titulo1=ARG4
titulo2=ARG5

set xlabel 'Numero de ciudades'		# Titulo del eje x
set ylabel 'Tiempo(seg)'

if (ARG1 == 1) {		# Si no comparar

	set terminal 'jpeg'
	set output 'Salida_ajustada1.jpeg'
	
	f(x)=a0 *x * log(x)
	fit f(x) datos1 via a0
	
	plot datos1 title "DyV", f(x) title 'Curva ajustada'
	
} else {
	
	if(ARG1 == 2){

		set terminal 'jpeg'
		set output 'Salida_comparativa.jpeg'
		
        # Determinar el tamaño de los ejes
		#set xrange [0:56]
		#set yrange [0:400]
		
		# Cómo ajustar las funciones 
		f(x)=a0* (2**x)
		fit f(x) datos1 via a0
		
		g(x)=a1* ((1.618034)**x)
		fit g(x) datos2 via a1
		
		plot datos1 title titulo1, datos2 title titulo2, f(x) title 'Ajuste1', g(x) title 'Ajuste2'
		
	}
}


#!/bin/gnuplot

# <datos1> <datos2> <datos3> <datos4> <datos5> <nombre_datos1> <nombre_datos2> <nombre_datos3> <nombre_datos4> <nombre_datos5>

datos1="u".ARG1.".dat"
datos2="u".ARG2.".dat"
datos3="u".ARG3.".dat"
datos4="u".ARG4.".dat"
datos5="u".ARG5.".dat"
datos6="u".ARG6.".dat"

titulo1=ARG1
titulo2=ARG2
titulo3=ARG3
titulo4=ARG4
titulo5=ARG5
titulo6=ARG6

set xlabel 'Tamaño (n)'		# Titulo del eje x
set ylabel 'Tiempo(seg)'


		set terminal 'png'
		set output 'Salida_comparativa.png'
		
        # Determinar el tamaño de los ejes
		
		#set yrange [0:400]
		
		# Cómo ajustar las funciones 
		f(x)=a0*x*x+b0*x+c0
		fit f(x) datos1 via a0,b0,c0
		
		g(x)=a1*x*x+b1*x+c1
		fit g(x) datos2 via a1,b1,c1
		
		h(x)=a2*x*x+b2*x+c2
		fit h(x) datos3 via a2,b2,c2
		
		i(x)=a3*x*x+b3*x+c3
		fit i(x) datos4 via a3,b3,c3
		
		j(x)=a4*x*x+b4*x+c4
		fit j(x) datos5 via a4,b4,c4
		
		k(x)=a5*x*x+b5*x+c5
		fit k(x) datos6 via a5,b5,c5
		
		#set xrange [0:200]
		
		plot datos1 title titulo1, datos2 title titulo2, datos3 title titulo3, datos4 title titulo4, datos5 title titulo5, datos6 title titulo6, f(x) title titulo1, g(x) title titulo2, h(x) title titulo3, i(x) title titulo4, j(x) title titulo5, k(x) title titulo6
		
		



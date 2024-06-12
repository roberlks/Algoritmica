#!/bin/gnuplot

# <numero de entradas> <datos1> <datos2> <nombre_datos1> <nombre_datos2>

decision=ARG1   	# Si numero de entradas es == 1 entonces solo hace regresion, si es 2 hace la comparacion

datos1=ARG2
datos2=ARG3

titulo1=ARG4
titulo2=ARG5

datos3=ARG6
titulo3=ARG7

set xlabel 'Num ciudades (n)'		# Titulo del eje x
set ylabel 'Tiempo (seg)'

if (ARG1 == 1) {		# Si no comparar

	set terminal 'png'
	set output 'Salida_ajustada1.png'
	
	f(x)=a0*x*x+b0*x+c0
	fit f(x) datos1 via a0,b0,c0
	
	plot datos1 title "TSP V2", f(x) title 'Curva ajustada'
	
} else {
	
	if(ARG1 == 2){

		set terminal 'png'
		set output 'Salida_comparativa.png'
		
        # Determinar el tamaño de los ejes
		
		#set yrange [0:400]
		
		# Cómo ajustar las funciones 
		f(x)=a0*x*x+b0*x+c0
		fit f(x) datos1 via a0,b0,c0
		
		g(x)=a1*x*x+b1*x+c1
		fit g(x) datos2 via a1,b1,c1
		
		solucion_x=((b1-b0)+sqrt((b0-b1)*(b0-b1)-4*(a0-a1)*(c0-c1)))/(2*(a0-a1))
		solucion_y=f(solucion_x)
		
		solucion2_x=((b1-b0)-sqrt((b0-b1)*(b0-b1)-4*(a0-a1)*(c0-c1)))/(2*(a0-a1))
		solucion2_y=f(solucion2_x)
		
		set xrange [0:200]
		
		plot datos1 title titulo1, datos2 title titulo2, f(x) title 'Ajuste1', g(x) title 'Ajuste2'
		
		print sprintf("Punto de intersección 1: (%.2f, %.2f)", solucion_x, solucion_y)
		print sprintf("Punto de intersección 2: (%.2f, %.2f)", solucion2_x, solucion2_y)
		
		set label 1 sprintf("(%.2f, %.2f)", solucion_x, solucion_y) at solucion_x, solucion_y point pt 7 offset 0.5,0.5
		
	}else {
		if(ARG1 == 3){
		set terminal 'png'
		set output 'Salida_comparativa.png'

		f(x)=a0*x*x+b0*x+c0
		fit f(x) datos1 via a0,b0,c0
		
		g(x)=a1*x*x+b1*x+c1
		fit g(x) datos2 via a1,b1,c1

		h(x)=a2*x*x*x+b2*x*x+c2*x + d
		fit h(x) datos3 via a2,b2,c2,d

		plot datos1 title titulo1, datos2 title titulo2,  datos3 title titulo3, f(x) title 'Ajuste1', g(x) title 'Ajuste2', h(x) title 'Ajuste3'
		}
	}
}


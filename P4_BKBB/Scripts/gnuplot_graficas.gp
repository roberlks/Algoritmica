#!/bin/gnuplot

# <numero de entradas> <datos1> <version> 

decision=ARG1   	# Si numero de entradas es == 1 entonces solo hace regresion, si es 2 hace la comparacion
datos1=ARG2
titulo1="TSPV".ARG3

set xlabel 'Nº ciudades (n)'		# Titulo del eje x
set ylabel 'Nodos generados'

if (ARG1 == 1) {		# Si no comparar

	set terminal 'png'
	
    set output 'salidaSoloPuntos.png'
	plot datos1 title titulo1 with points
	set output 'salidaSoloLineas.png'
	plot datos1 title titulo1 with lines
    
} else {
    
    set terminal 'png'

    set output 'Nodes/Graphs/Output/CurvaAjustada_n1.png'
    f(x) = a*x + b
	fit f(x) datos1 via a,b
	plot datos1 title titulo1, f(x) title 'Curva ajustada'

    set output 'Nodes/Graphs/Output/CurvaAjustada_n2.png'
    f(x)=a*x*x + b*x + c
	fit f(x) datos1 via a,b,c
	plot datos1 title titulo1, f(x) title 'Curva ajustada'

    set output 'Nodes/Graphs/Output/CurvaAjustada_n3.png'
    f(x)=a*x*x*x + b*x*x + c*x + d
	fit f(x) datos1 via a,b,c,d
	plot datos1 title titulo1, f(x) title 'Curva ajustada'

    set output 'Nodes/Graphs/Output/CurvaAjustada_n4.png'
    f(x)=a*x*x*x*x + b*x*x*x + c*x*x + d*x + e
	fit f(x) datos1 via a,b,c,d,e
	plot datos1 title titulo1, f(x) title 'Curva ajustada'
	
    set output 'Nodes/Graphs/Output/CurvaAjustada_n5.png'
    f(x)=a*x*x*x*x*x + b*x*x*x*x + c*x*x*x + d*x*x + e*x + f
	fit f(x) datos1 via a,b,c,d,e,f
	plot datos1 title titulo1, f(x) title 'Curva ajustada'
    
    set output 'Nodes/Graphs/Output/CurvaAjustada_n6.png'
    f(x)=a*x*x*x*x*x*x + b*x*x*x*x*x + c*x*x*x*x + d*x*x*x + e*x*x + f*x +g
	fit f(x) datos1 via a,b,c,d,e,f,g
	plot datos1 title titulo1, f(x) title 'Curva ajustada'
    
    set output 'Nodes/Graphs/Output/CurvaAjustada_n7.png'
    f(x)=a*x*x*x*x*x*x*x + b*x*x*x*x*x*x + c*x*x*x*x*x + d*x*x*x*x + e*x*x*x + f*x*x + g*x +h
	fit f(x) datos1 via a,b,c,d,e,f,g,h
	plot datos1 title titulo1, f(x) title 'Curva ajustada'
	
    set output 'Nodes/Graphs/Output/CurvaAjustada_n8.png'
    f(x)=a*x*x*x*x*x*x*x*x + b*x*x*x*x*x*x*x + c*x*x*x*x*x*x + d*x*x*x*x*x*x + e*x*x*x*x + f*x*x*x + g*x*x + h*x + i
	fit f(x) datos1 via a,b,c,d,e,f,g,h,i
	plot datos1 title titulo1, f(x) title 'Curva ajustada'
	
    set output 'Nodes/Graphs/Output/CurvaAjustada_n9.png'
    f(x)=a*x*x*x*x*x*x*x*x*x + b*x*x*x*x*x*x*x*x + c*x*x*x*x*x*x*x + d*x*x*x*x*x*x + e*x*x*x*x*x + f*x*x*x*x + g*x*x*x + h*x*x + i*x + j
	fit f(x) datos1 via a,b,c,d,e,f,g,h,i,j
	plot datos1 title titulo1, f(x) title 'Curva ajustada'

	set output 'Nodes/Graphs/Output/CurvaAjustada_exp.png'
    f(x)=a0*x*x*x*exp(b0*x)
	fit f(x) datos1 via a0,b0
	plot datos1 title titulo1, f(x) title 'Curva ajustada'
}


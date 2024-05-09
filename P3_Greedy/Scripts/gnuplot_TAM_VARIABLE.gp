#!/bin/gnuplot

# Dado un tamaño variable de fichero de datos, los plotea todos en una misma grafica 
# por lineas. 
# ARG1: nombre de TODOS los ficheros datos separados por espacio. IMPORTANTE: al introducirlos tienen que estar todos
#       entre un mismo par de comillas. Ejem: 'dato1 dato2 dato_3'
# ARG2: nombre de TODOS los titulos de los datos separados por espacio. IMPORTANTE: al introducirlos tienen que estar todos
#       entre un mismo par de comillas. Ejem: 'titulo1 titulo2 titulo_3'
# ARG3: nombre del fichero de salida (preferiblemente con extensión jpeg)
# ARG4: titulo para el eje x
# ARG5: titulo para el eje y


# <"dato1 dato2...dato_n"> <"titulo1 titulo2...titulo_n"> <fichero_salida.jpeg> <TITULO_X> <TITULO_Y>

set terminal 'png'
set output ARG3."_line.png"

set xlabel ARG4
set ylabel ARG5

plot for [i=1:words(ARG1)] word(ARG1, i) title word(ARG2, i) with lines
set output ARG3."_points.png"
plot for [i=1:words(ARG1)] word(ARG1, i) title word(ARG2, i) with points 

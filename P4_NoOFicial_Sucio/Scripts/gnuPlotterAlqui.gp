#!/usr/bin/gnuplot

# Verificar si se proporcionaron los tres archivos como argumentos
if (ARGC != 6) {
    print "Uso: gnuplot mi_script.gp BB1.dat BB2.dat BB3.dat BK1.dat BK2.dat BK3.dat"
    exit 1
}

# Asignar los nombres de los archivos a variables
cota1 = ARG1
cota2 = ARG2
cota3 = ARG3
cota4 = ARG4
cota5 = ARG5
cota6 = ARG6

# Configurar la salida de la gráfica (por ejemplo, en formato PNG)
set terminal pngcairo
set output "mi_grafica.png"

# Título de la gráfica y etiquetas de los ejes
set title "Gráfica de Cotas"
set xlabel "Nº ciudades"
set ylabel "Tiempo en segs"

# Comando para graficar las tres cotas
plot cota1 title "BB1" with linespoints, \
     cota2 title "BB2" with linespoints, \
     cota3 title "BB3" with linespoints, \
     cota4 title "BK1" with linespoints, \
     cota5 title "BK2" with linespoints, \
     cota6 title "BK3" with linespoints

# Guardar la gráfica
replot

# Salir de gnuplot
exit

set terminal pngcairo enhanced font 'Verdana,12'
set output 'grafica.png'

# Configuración de la leyenda
set key top left

# Configuración de los colores y estilos de las líneas
set style line 1 lc rgb '#1f77b4' lt 1 lw 2 pt 7 pi -1 ps 0.5 # azul
set style line 2 lc rgb '#ff7f0e' lt 1 lw 2 pt 5 pi -1 ps 0.5 # naranja
set style line 3 lc rgb '#2ca02c' lt 1 lw 2 pt 9 pi -1 ps 0.5 # verde
set style line 4 lc rgb '#ff0000' lt 1 lw 2 pt 9 pi -1 ps 0.5 # rojo
set style line 5 lc rgb '#ffff00' lt 1 lw 2 pt 9 pi -1 ps 0.5 # amarillo


# Configuración de la etiqueta de la leyenda
set label "197" at graph 0.01, 0.95 tc ls 1
set label "207" at graph 0.01, 0.90 tc ls 2
set label "217" at graph 0.01, 0.85 tc ls 3
set label "227" at graph 0.01, 0.80 tc ls 4
set label "237" at graph 0.01, 0.75 tc ls 5

# Configuración de los títulos de los ejes
set xlabel "Tamaño"
set ylabel "Tiempo"

# Graficar los datos
plot "times_u197.dat" with lines ls 1 title "", \
     "times_u207.dat" with lines ls 2 title "", \
     "times_u217.dat" with lines ls 3 title "", \
     "times_u227.dat" with lines ls 4 title "", \
     "times_u237.dat" with lines ls 5 title ""

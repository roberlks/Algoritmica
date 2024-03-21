# Recibe 'sort_type', 'plot_style' y 'data_types' del shell script
reset
# Configuraciones iniciales
set title "Comparación de eficiencia para distintos tipos de datos"
set xlabel "Tamaño de los datos"
set ylabel "Tiempo (s)"
set grid
#set key outside right top

# Estilos de línea/punto
#set style line 1 lc rgb 'blue' pt 7 ps 1.5
#set style line 2 lc rgb 'red' pt 11 ps 1.5
#set style line 3 lc rgb 'green' pt 9 ps 1.5
#set style line 4 lc rgb 'orange' pt 13 ps 1.5

# Configurar salida
output_directory = '../Datos/'.sort_type.'_data/graphs/'
output_filename = ''.output_directory.''.sort_type.'_comparison_'.plot_style.'.png'

set terminal png size 650,279 enhanced font 'Verdana,10'
set output output_filename

# Construye la cadena de plot basado en los tipos de datos proporcionados
data_types_array = system("echo ".data_types." | tr ',' ' '")
plot_string = ""
do for [data_type in data_types_array] {
    data_file = '"../Datos/'.sort_type.'_data/dats/'.sort_type.'_'.data_type.'.dat"'
    title_str = '"'.data_type.'"'
    if (strlen(plot_string) > 0) {
        plot_string = plot_string.', '
    }
    plot_string = plot_string.data_file.' using 1:2 '.plot_style.' linestyle '.strstrt("int float double string", data_type).' title '.title_str
}

# Ejecuta el plot
eval("plot ".plot_string)

# Cerrar el archivo de salida
set output

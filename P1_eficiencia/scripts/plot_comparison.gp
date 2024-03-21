# Asume que los tipos de datos han sido pasados como una cadena separada por espacios
# Ejemplo de invocación: gnuplot -e "data_types='int float double string'" compare_sorts.gp

# Configuraciones iniciales
set xlabel "Tamaño de los datos"
set ylabel "Tiempo (s)"
set grid
#set key outside right top

# Asume que el script se ejecuta desde el directorio que contiene 'Datos'

# Configuraciones iniciales ...
set terminal png size 650,279 enhanced font 'Verdana,10'

# Para cada tipo de datos, se genera un gráfico
data_types_array = system("echo ".data_types." | tr ' ' '\n'")  # Convierte la cadena en un array

do for [data_type in data_types_array] {
    set title "Comparación de eficiencia entre Quicksort y Mergesort - ".data_type
    output_filename = "Comparativas/comparacion_sorts_".data_type.".png"
    set output output_filename

    quicksort_file = '../Datos/quicksort_data/dats/quicksort_'.data_type.'.dat'
    mergesort_file = '../Datos/mergesort_data/dats/mergesort_'.data_type.'.dat'

    plot quicksort_file using 1:2 with lines linestyle 1 title "Quicksort ".data_type, \
         mergesort_file using 1:2 with lines linestyle 2 title "Mergesort ".data_type
}

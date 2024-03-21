#!/bin/bash

# Asigna los argumentos a variables
SORT_TYPE=$1  # El primer argumento: 'mergesort' o 'quicksort'
GRAPH_TYPE=$2  # El segundo argumento: 'lineas' o 'puntos'
# A continuación, toma un conjunto de argumentos opcionales para los tipos de datos
DATA_TYPES=("${@:3}")  # Todos los argumentos desde el tercero en adelante

# Comprueba que se hayan proporcionado los argumentos necesarios
if [ -z "$SORT_TYPE" ] || [ -z "$GRAPH_TYPE" ]; then
    echo "Uso: $0 {mergesort|quicksort} {lineas|puntos} [tipos de dato...]"
    exit 1
fi

# Define el estilo del gráfico en función del segundo argumento
if [ "$GRAPH_TYPE" == "lineas" ]; then
    PLOT_STYLE="lines"
elif [ "$GRAPH_TYPE" == "puntos" ]; then
    PLOT_STYLE="points"
else
    echo "El tipo de gráfico no es válido: elige 'lineas' o 'puntos'"
    exit 1
fi

# Crea el directorio si no existe
OUTPUT_DIR="../Datos/${SORT_TYPE}_data/graphs"
mkdir -p "$OUTPUT_DIR"

# Verifica si se proporcionaron tipos de dato. Si no, usa un conjunto predeterminado.
if [ ${#DATA_TYPES[@]} -eq 0 ]; then
    DATA_TYPES=("int" "float" "double" "string")  # Cambia esto por los tipos de datos que desees como predeterminados
fi

# Construye una lista separada por comas sin comillas para los tipos de datos
DATA_TYPES_STR=$(IFS=, ; echo "${DATA_TYPES[*]}")

# Llama a Gnuplot pasando las variables como macros
gnuplot -e "sort_type='$SORT_TYPE'; plot_style='with $PLOT_STYLE'; data_types='$DATA_TYPES_STR'" plot_sorts.gp

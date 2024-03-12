#!/bin/bash

# Asigna el argumento a una variable
GRAPH_TYPE=$1  # El primer argumento: 'lineas' o 'puntos'
# A continuación, toma un conjunto de argumentos opcionales para los tipos de datos
DATA_TYPES=("${@:2}")  # Todos los argumentos desde el segundo en adelante

# Comprueba que se haya proporcionado el argumento necesario
if [ -z "$GRAPH_TYPE" ]; then
    echo "Uso: $0 {lineas|puntos} [tipos de dato...]"
    exit 1
fi

# Define el estilo del gráfico en función del primer argumento
if [ "$GRAPH_TYPE" == "lineas" ]; then
    PLOT_STYLE="with lines"
elif [ "$GRAPH_TYPE" == "puntos" ]; then
    PLOT_STYLE="with points"
else
    echo "El tipo de gráfico no es válido: elige 'lineas' o 'puntos'"
    exit 1
fi

# Crea el directorio si no existe
OUTPUT_DIR="./Comparativas"
mkdir -p "$OUTPUT_DIR"

# Verifica si se proporcionaron tipos de dato. Si no, usa un conjunto predeterminado.
if [ ${#DATA_TYPES[@]} -eq 0 ]; then
    DATA_TYPES=("int" "float" "double" "string")  # Cambia esto por los tipos de datos que desees como predeterminados
fi

# Crea una cadena de datos separada por espacios para pasarlo al script de Gnuplot
DATA_TYPES_STR="${DATA_TYPES[*]}"

# Llama a Gnuplot pasando las variables como macros
gnuplot -e "plot_style='with $PLOT_STYLE'; data_types='$DATA_TYPES_STR'" plot_comparison.gp

#!/bin/bash

# Asegúrate de que se proporcionan todos los argumentos necesarios
if [ "$#" -ne 3 ]; then
    echo "Uso: $0 <ruta_carpeta_txt> <ruta_ejecutable> <ruta_archivo_salida>"
    exit 1
fi

# Asignar los argumentos a variables para mejorar la legibilidad
carpeta_txt=$1
ejecutable=$2
archivo_salida=$3

# Borrar el contenido del archivo de salida para empezar fresco, opcional
> "$archivo_salida"

# Iterar sobre cada archivo .txt en la carpeta
for archivo in "$carpeta_txt"/*.txt
do
    # Ejecutar el ejecutable con el archivo como entrada y añadir la salida al archivo de salida
    $ejecutable $archivo >> "$archivo_salida"
    # Añadir un salto de línea después de cada ejecución para separar las salidas
done

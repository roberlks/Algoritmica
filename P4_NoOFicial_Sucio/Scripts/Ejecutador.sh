#!/bin/bash

if [ "$#" -ne 5 ]; then
    echo "Uso: $0 <ejecutable> <carpeta de instancias> <inicio de los niN.txt> <fin> <valor de la f de cota>"
    exit 1
fi

ejecutable=$1
carpeta=$2
inicio=$3
fin=$4
valor=$5
output_file="times.dat"

# Limpiar o crear el archivo de salida
> $output_file

# Iterar sobre el rango especificado de archivos
for ((i=inicio; i<=fin; i++)); do
    archivo="$carpeta/ni$i.txt"
    if [ -f "$archivo" ]; then
        $ejecutable $archivo $valor >> $output_file
    else
        echo "Archivo $archivo no existe, se salta."
    fi
done

echo "Ejecución completada. Resultados guardados en $output_file."

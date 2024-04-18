#!/bin/bash

# Verifica que se hayan proporcionado los argumentos necesarios
if [ "$#" -ne 5 ]; then
    echo "Uso: $0 <ruta_ejecutable> <valor_minimo> <valor_maximo> <n_salto> <nombre_salida>"
    exit 1
fi

ejecutable=$1
valor_minimo=$2
valor_maximo=$3
n_salto=$4
nombre_salida_grafica="tiempos_$5"

path="../Tiempos/" # Directorio para los datos
datapath="${path}$5.dat" # Ruta y nombre del archivo .dat

# Crea el directorio si no existe
mkdir -p $path

# Limpia el archivo de resultados anterior, si existe
> "${datapath}"

# Ejecuta el programa con los valores especificados y guarda los resultados en el archivo .dat
for (( i = valor_minimo; i <= valor_maximo; i = i + n_salto )); do 
    ./$ejecutable $i >> "${datapath}"
done

# Verifica si el script de gnuplot existe
g1_path="./g1.gp" # Asegúrate de ajustar esta ruta según sea necesario
if [ ! -f "$g1_path" ]; then
    echo "El script $g1_path no existe."
    exit 2
fi

mkdir -p $(dirname "${path}${nombre_salida_grafica}.png")

scriptgnuplot="g1.gp"
#<nombre_fichero_datos> <titulo de la grafica> <etiqueta_x> <nombre_salida.png> <1 ó 2>
gnuplot -c $scriptgnuplot "${datapath}" "${nombre_salida_grafica}" "Tam datos (n)" "${path}${nombre_salida_grafica}_Lineas.png" "1"
gnuplot -c $scriptgnuplot "${datapath}" "${nombre_salida_grafica}" "Tam datos (n)" "${path}${nombre_salida_grafica}_Puntos.png" "2"

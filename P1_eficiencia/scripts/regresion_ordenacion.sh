#!/bin/bash

# Algoritmos y tipos de datos
algoritmos=("burbuja" "insercion")
tipos=("int" "float" "double" "string")

# Recorrer cada algoritmo
for algoritmo in "${algoritmos[@]}"; do
    # Recorrer cada tipo de dato
    for tipo in "${tipos[@]}"; do
        gnuplot -c $algoritmo $tipo cuadratico
    done
done

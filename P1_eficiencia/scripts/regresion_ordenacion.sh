#!/bin/bash

# Algoritmos y tipos de datos
algoritmos=("mergesort" "quicksort")
tipos=("int" "float" "double" "string")

# Recorrer cada algoritmo
for algoritmo in "${algoritmos[@]}"; do
    # Recorrer cada tipo de dato
    for tipo in "${tipos[@]}"; do
        gnuplot -c "regresion_ordenacion.gp" $algoritmo $tipo "linear logaritmico"
    done
done

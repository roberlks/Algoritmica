#!/bin/bash

# Algoritmos y tipos de datos
algoritmos=("burbuja" "insercion")
tipos=("string")

# Recorrer cada algoritmo
for algoritmo in "${algoritmos[@]}"; do
    # Recorrer cada tipo de dato
    for tipo in "${tipos[@]}"; do
        echo "Ejecutando ${algoritmo}_${tipo}..."
        if [[ "$tipo" == "string" ]]; then
        	./recoger_datos2.sh "$algoritmo" "$tipo" 12308 202308 10000
        else
        	./recoger_datos2.sh "$algoritmo" "$tipo" 5000 125000 5000
        fi
        echo "Finalizado ${algoritmo}_${tipo}..."
    done
done

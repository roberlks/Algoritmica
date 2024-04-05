# Definición de variables
DYV_DIR=./DyV
ESPEC_DIR=./Especifico
GEN_DIR=./Generador

# Nombres de los ejecutables
DYV_EXECUTABLE=$(DYV_DIR)/dyv
ESPEC_EXECUTABLE=$(ESPEC_DIR)/especifico
GEN_EXECUTABLE=$(GEN_DIR)/generador

# Compilación de los ejecutables
all: $(DYV_EXECUTABLE) $(ESPEC_EXECUTABLE) $(GEN_EXECUTABLE)

$(DYV_EXECUTABLE): $(DYV_DIR)/dyv.cpp
	g++ $< -o $@

$(ESPEC_EXECUTABLE): $(ESPEC_DIR)/especifico.cpp
	g++ $< -o $@

$(GEN_EXECUTABLE): $(GEN_DIR)/generador.cpp
	g++ $< -o $@

# Regla para limpiar los archivos generados
clean:
	rm -f $(DYV_EXECUTABLE) $(ESPEC_EXECUTABLE) $(GEN_EXECUTABLE)

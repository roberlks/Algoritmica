# Definición de variables
DYV_DIR=./DyV
ESPEC_DIR=./Especifico
GEN_DIR=./Generador
INC_DIR=.

# Nombres de los ejecutables
DYV_EXECUTABLE=$(DYV_DIR)/dyv
ESPEC_EXECUTABLE=$(ESPEC_DIR)/especifico
GEN_EXECUTABLE=$(GEN_DIR)/generador

# Compilación de los ejecutables
all: $(DYV_EXECUTABLE) $(ESPEC_EXECUTABLE) $(GEN_EXECUTABLE)

$(DYV_EXECUTABLE): $(DYV_DIR)/dyv.cpp $(INC_DIR)/City.h
	g++ -I$(INC_DIR) $< -o $@

$(ESPEC_EXECUTABLE): $(ESPEC_DIR)/especifico.cpp $(INC_DIR)/City.h
	g++ -I$(INC_DIR) $< -o $@

$(GEN_EXECUTABLE): $(GEN_DIR)/generador.cpp $(INC_DIR)/City.h
	g++ -I$(INC_DIR) $< -o $@

# Regla para limpiar los archivos generados
clean:
	rm -f $(DYV_EXECUTABLE) $(ESPEC_EXECUTABLE) $(GEN_EXECUTABLE)

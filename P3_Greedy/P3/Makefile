# Definición de variables
GREEDY_DIR=./Greedy
GEN_DIR=./Generador
INC_DIR=../Include

# Nombres de los ejecutables
GREEDY_EXE=$(GREEDY_DIR)/greedy
GEN_EXE=$(GEN_DIR)/generador
VISUAL_GEN_EXE=$(GEN_DIR)/visual_generator

# Compilación de los ejecutables
all: $(GREEDY_EXE) $(GEN_EXE)

$(GREEDY_EXE): $(GREEDY_DIR)/greedy.cpp $(INC_DIR)/City.h
	g++ -I$(INC_DIR) $< -o $@

$(GEN_EXE): $(GEN_DIR)/generador.cpp $(INC_DIR)/City.h
	g++ -I$(INC_DIR) $< -o $@

$(VISUAL_GEN_EXE): $(GEN_DIR)/generador.cpp $(INC_DIR)/City.h
	g++ -I$(INC_DIR) $< -o $@ -D VISUAL

# Regla para limpiar los archivos generados
clean:
	rm -f $(GREEDY_EXE) $(GEN_EXE) $(VISUAL_GEN_EXE)
	rm -rf ./*/output*
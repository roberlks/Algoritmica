# Directorios
GEN_DIR=./Generador
SRC_DIR=./Greedy
BIN_DIR=./Greedy
INC_DIR=../Include

# Objetivos para la compilación
TARGETS = $(GEN_DIR)/generador $(GEN_DIR)/visual_generator $(BIN_DIR)/V1/greedy $(BIN_DIR)/V2/greedy $(BIN_DIR)/V3/greedy

# Archivos fuente
GEN_SRC = $(GEN_DIR)/generador.cpp
V1_SRC = $(SRC_DIR)/V1/greedy.cpp
V2_SRC = $(SRC_DIR)/V2/greedy.cpp
V3_SRC = $(SRC_DIR)/V3/greedy.cpp

# Compilación
all: $(TARGETS)

$(GEN_DIR)/generador: $(GEN_SRC)
	g++ -I$(INC_DIR) $< -o $@

$(GEN_DIR)/visual_generator: $(GEN_DIR)/generador.cpp $(INC_DIR)/City.h
	g++ -I$(INC_DIR) $< -o $@ -D VISUAL

$(BIN_DIR)/V1/greedy: $(V1_SRC)
	g++ -I$(INC_DIR) $< -o $@

$(BIN_DIR)/V2/greedy: $(V2_SRC)
	g++ -I$(INC_DIR) $< -o $@

$(BIN_DIR)/V3/greedy: $(V3_SRC)
	g++ -I$(INC_DIR) $< -o $@


clean:
	rm -f $(TARGETS)
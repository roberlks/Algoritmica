# Directorios
GEN_DIR=./Generador
SRC_DIR=./Algoritmo
BIN_DIR=./Algoritmo
INC_DIR=../Include

# Objetivos para la compilación
TARGETS = $(GEN_DIR)/generador $(GEN_DIR)/visual_generator $(BIN_DIR)/algoritmo
TIME_TARGETS= $(GEN_DIR)/generador $(BIN_DIR)/algoritmo_time
COST_TARGETS= $(GEN_DIR)/generador $(BIN_DIR)/algoritmo_cost

# Archivos fuente
GEN_SRC = $(GEN_DIR)/generador.cpp
SRC = $(SRC_DIR)/algoritmo.cpp

# Compilación
all: $(TARGETS)

$(GEN_DIR)/generador: $(GEN_SRC) $(INC_DIR)/City.h
	g++ -I$(INC_DIR) $< -o $@

$(GEN_DIR)/visual_generator: $(GEN_SRC) $(INC_DIR)/City.h
	g++ -I$(INC_DIR) $< -o $@ -D VISUAL

$(BIN_DIR)/algoritmo: $(SRC) $(INC_DIR)/City.h
	g++ -I$(INC_DIR) $< -o $@

time: $(TIME_TARGETS)

$(BIN_DIR)/algoritmo_time: $(SRC) $(INC_DIR)/City.h
	g++ -I$(INC_DIR) $< -o $@ -D TIME

cost: $(COST_TARGETS)

$(BIN_DIR)/algoritmo_cost: $(SRC) $(INC_DIR)/City.h
	g++ -I$(INC_DIR) $< -o $@ -D COST

clean:
	rm -f $(TARGETS) $(TIME_TARGETS)  $(COST_TARGETS)

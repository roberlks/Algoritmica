# Directorios
GEN_DIR=./Generador
SRC_DIR=./Algoritmo
BIN_DIR=./Algoritmo
INC_DIR=../Include

# Objetivos para la compilación
TARGETS = $(GEN_DIR)/generador $(GEN_DIR)/visual_generator $(BIN_DIR)/V1/algoritmo $(BIN_DIR)/V2/algoritmo $(BIN_DIR)/V3/algoritmo
TIME_TARGETS= $(GEN_DIR)/generador $(BIN_DIR)/V1/algoritmo_time $(BIN_DIR)/V2/algoritmo_time $(BIN_DIR)/V3/algoritmo_time
COST_TARGETS= $(GEN_DIR)/generador $(BIN_DIR)/V1/algoritmo_cost $(BIN_DIR)/V2/algoritmo_cost $(BIN_DIR)/V3/algoritmo_cost

# Archivos fuente
GEN_SRC = $(GEN_DIR)/generador.cpp
V1_SRC = $(SRC_DIR)/V1/algoritmo.cpp
V2_SRC = $(SRC_DIR)/V2/algoritmo.cpp
V3_SRC = $(SRC_DIR)/V3/algoritmo.cpp

# Compilación
all: $(TARGETS)

$(GEN_DIR)/generador: $(GEN_SRC) $(INC_DIR)/City.h
	g++ -I$(INC_DIR) $< -o $@

$(GEN_DIR)/visual_generator: $(GEN_SRC) $(INC_DIR)/City.h
	g++ -I$(INC_DIR) $< -o $@ -D VISUAL

$(BIN_DIR)/V1/algoritmo: $(V1_SRC) $(INC_DIR)/City.h
	g++ -I$(INC_DIR) $< -o $@

$(BIN_DIR)/V2/algoritmo: $(V2_SRC) $(INC_DIR)/City.h
	g++ -I$(INC_DIR) $< -o $@

$(BIN_DIR)/V3/algoritmo: $(V3_SRC) $(INC_DIR)/City.h
	g++ -I$(INC_DIR) $< -o $@

time: $(TIME_TARGETS)

$(BIN_DIR)/V1/algoritmo_time: $(V1_SRC) $(INC_DIR)/City.h
	g++ -I$(INC_DIR) $< -o $@ -D TIME

$(BIN_DIR)/V2/algoritmo_time: $(V2_SRC) $(INC_DIR)/City.h
	g++ -I$(INC_DIR) $< -o $@ -D TIME

$(BIN_DIR)/V3/algoritmo_time: $(V3_SRC) $(INC_DIR)/City.h
	g++ -I$(INC_DIR) $< -o $@ -D TIME

cost: $(COST_TARGETS)

$(BIN_DIR)/V1/algoritmo_cost: $(V1_SRC) $(INC_DIR)/City.h
	g++ -I$(INC_DIR) $< -o $@ -D COST

$(BIN_DIR)/V2/algoritmo_cost: $(V2_SRC) $(INC_DIR)/City.h
	g++ -I$(INC_DIR) $< -o $@ -D COST

$(BIN_DIR)/V3/algoritmo_cost: $(V3_SRC) $(INC_DIR)/City.h
	g++ -I$(INC_DIR) $< -o $@ -D COST
clean:
	rm -f $(TARGETS) $(TIME_TARGETS)  $(COST_TARGETS)

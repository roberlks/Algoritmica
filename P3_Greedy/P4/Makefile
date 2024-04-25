# Directorios
GEN_DIR=./Generador
SRC_DIR=./Greedy
BIN_DIR=./Greedy
INC_DIR=../Include

# Objetivos para la compilación
TARGETS = $(GEN_DIR)/generador $(GEN_DIR)/visual_generator $(BIN_DIR)/V1/greedy $(BIN_DIR)/V2/greedy $(BIN_DIR)/V3/greedy
TIME_TARGETS= $(GEN_DIR)/generador $(BIN_DIR)/V1/greedy_time $(BIN_DIR)/V2/greedy_time $(BIN_DIR)/V3/greedy_time
COST_TARGETS= $(GEN_DIR)/generador $(BIN_DIR)/V1/greedy_cost $(BIN_DIR)/V2/greedy_cost $(BIN_DIR)/V3/greedy_cost

# Archivos fuente
GEN_SRC = $(GEN_DIR)/generador.cpp
V1_SRC = $(SRC_DIR)/V1/greedy.cpp
V2_SRC = $(SRC_DIR)/V2/greedy.cpp
V3_SRC = $(SRC_DIR)/V3/greedy.cpp

# Compilación
all: $(TARGETS)

$(GEN_DIR)/generador: $(GEN_SRC) $(INC_DIR)/City.h
	g++ -I$(INC_DIR) $< -o $@

$(GEN_DIR)/visual_generator: $(GEN_SRC) $(INC_DIR)/City.h
	g++ -I$(INC_DIR) $< -o $@ -D VISUAL

$(BIN_DIR)/V1/greedy: $(V1_SRC) $(INC_DIR)/City.h
	g++ -I$(INC_DIR) $< -o $@

$(BIN_DIR)/V2/greedy: $(V2_SRC) $(INC_DIR)/City.h
	g++ -I$(INC_DIR) $< -o $@

$(BIN_DIR)/V3/greedy: $(V3_SRC) $(INC_DIR)/City.h
	g++ -I$(INC_DIR) $< -o $@

time: $(TIME_TARGETS)

$(BIN_DIR)/V2/greedy_time: $(V2_SRC) $(INC_DIR)/City.h
	g++ -I$(INC_DIR) $< -o $@ -D TIME

$(BIN_DIR)/V3/greedy_time: $(V3_SRC) $(INC_DIR)/City.h
	g++ -I$(INC_DIR) $< -o $@ -D TIME

cost: $(COST_TARGETS)

$(BIN_DIR)/V2/greedy_cost: $(V2_SRC) $(INC_DIR)/City.h
	g++ -I$(INC_DIR) $< -o $@ -D COST

$(BIN_DIR)/V3/greedy_cost: $(V3_SRC) $(INC_DIR)/City.h
	g++ -I$(INC_DIR) $< -o $@ -D COST
clean:
	rm -f $(TARGETS) $(TIME_TARGETS)  $(COST_TARGETS)

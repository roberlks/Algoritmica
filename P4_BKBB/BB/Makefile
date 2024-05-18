# Directorios
GEN_DIR = ./Generador
ALG_DIR = ./Algoritmo
BIN_DIR = ./Algoritmo
INC_DIR = ../Include
SRC_DIR = ../Src

# Objetivos para la compilación
TARGETS = $(GEN_DIR)/generador $(GEN_DIR)/visual_generator $(BIN_DIR)/algoritmo
TIME_TARGETS = $(GEN_DIR)/generador $(BIN_DIR)/algoritmo_time
COST_TARGETS = $(GEN_DIR)/generador $(BIN_DIR)/algoritmo_cost
NODE_TARGETS = $(GEN_DIR)/generador $(BIN_DIR)/algoritmo_nodes

# Archivos fuente
GEN_SRC = $(GEN_DIR)/generador.cpp
ALG_SRC = $(ALG_DIR)/algoritmo.cpp
SOLUTION_SRC = $(SRC_DIR)/Solution.cpp
CITY_SRC = $(SRC_DIR)/City.cpp

# Compilación
all: $(TARGETS)

$(GEN_DIR)/generador: $(GEN_SRC) $(CITY_SRC) $(INC_DIR)/City.h
	g++ -I$(INC_DIR) $(GEN_SRC) $(CITY_SRC) -o $@

$(GEN_DIR)/visual_generator: $(GEN_SRC) $(CITY_SRC) $(INC_DIR)/City.h
	g++ -I$(INC_DIR) $(GEN_SRC) $(CITY_SRC) -o $@ -D VISUAL

$(BIN_DIR)/algoritmo: $(ALG_SRC) $(CITY_SRC) $(SOLUTION_SRC) $(INC_DIR)/City.h
	g++ -I$(INC_DIR) $(ALG_SRC) $(CITY_SRC) $(SOLUTION_SRC) -o $@

time: $(TIME_TARGETS)

$(BIN_DIR)/algoritmo_time: $(ALG_SRC) $(CITY_SRC) $(SOLUTION_SRC) $(INC_DIR)/City.h
	g++ -I$(INC_DIR) $(ALG_SRC) $(CITY_SRC) $(SOLUTION_SRC) -o $@ -D TIME

cost: $(COST_TARGETS)

$(BIN_DIR)/algoritmo_cost: $(ALG_SRC) $(CITY_SRC) $(SOLUTION_SRC) $(INC_DIR)/City.h
	g++ -I$(INC_DIR) $(ALG_SRC) $(CITY_SRC) $(SOLUTION_SRC) -o $@ -D COST

nodes: $(NODE_TARGETS)

$(BIN_DIR)/algoritmo_nodes: $(ALG_SRC) $(CITY_SRC) $(SOLUTION_SRC) $(INC_DIR)/City.h
	g++ -I$(INC_DIR) $(ALG_SRC) $(CITY_SRC) $(SOLUTION_SRC) -o $@ -D NODES

clean:
	rm -f $(TARGETS) $(TIME_TARGETS) $(COST_TARGETS) $(NODE_TARGETS)
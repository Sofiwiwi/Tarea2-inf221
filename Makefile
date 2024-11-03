# Compilador y banderas de compilación
CC = g++
CFLAGS = -std=c++11 -O2

# Carpetas de salida
OBJ_DIR = obj
BIN_DIR = bin

# Archivos fuente
COMMON_SRC = lec_cos.cpp
FUERZA_BRUTA_SRC = fuerzabruta.cpp
PROG_DINAMICA_SRC = progdin.cpp

# Archivos objeto
COMMON_OBJ = $(OBJ_DIR)/lec_cos.o
FUERZA_BRUTA_OBJ = $(OBJ_DIR)/fuerzabruta.o
PROG_DINAMICA_OBJ = $(OBJ_DIR)/progdin.o

# Ejecutables
FUERZA_BRUTA_EXEC = $(BIN_DIR)/fuerzabruta
PROG_DINAMICA_EXEC = $(BIN_DIR)/progdin

# Objetivo principal: compilar y ejecutar todo
# Objetivo principal: compilar y ejecutar todo
all: $(FUERZA_BRUTA_EXEC) $(PROG_DINAMICA_EXEC)
	@echo "Ejecutando fuerza_bruta..."
	./$(FUERZA_BRUTA_EXEC)
	@echo "Ejecutando programacion_dinamica..."
	./$(PROG_DINAMICA_EXEC)

# Compilar funciones comunes
$(COMMON_OBJ): $(COMMON_SRC) lec_cos.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(COMMON_SRC) -o $(COMMON_OBJ)

# Compilar fuerza bruta
$(FUERZA_BRUTA_EXEC): $(FUERZA_BRUTA_SRC) $(COMMON_OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(FUERZA_BRUTA_SRC) $(COMMON_OBJ) -o $(FUERZA_BRUTA_EXEC) 

# Compilar programación dinámica (bottom-up)
$(PROG_DINAMICA_EXEC): $(PROG_DINAMICA_SRC) $(COMMON_OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(PROG_DINAMICA_SRC) $(COMMON_OBJ) -o $(PROG_DINAMICA_EXEC)

# Crear carpeta para archivos objeto
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Crear carpeta para ejecutables
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Limpiar archivos generados
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Archivos .o y ejecutables eliminados."

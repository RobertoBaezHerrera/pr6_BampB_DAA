# Universidad de La Laguna
# Escuela Superior de Ingeniería y Tecnología
# Grado en Ingeniería Informática
# Diseño y Análisis de Algoritmos
# @authors:
# Roberto Báez Herrera

CXX = g++ # C++ compiler command
CXXFLAGS = -std=c++17 -g -Iinclude # C++ compiler options, including include directory
LDFLAGS = # Linker options (if any)

# Directorios
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

# Crear las carpetas si no existen
$(shell mkdir -p $(BUILD_DIR) $(BIN_DIR))

# Archivos fuente y objeto
SOURCES = $(wildcard $(SRC_DIR)/**/*.cc $(SRC_DIR)/*.cc)
OBJECTS = $(patsubst $(SRC_DIR)/%.cc, $(BUILD_DIR)/%.o, $(SOURCES))

# Nombre del ejecutable
EXECUTABLE = $(BIN_DIR)/pr5

# El objetivo por defecto compila todo
all: $(EXECUTABLE)

# Regla para compilar el ejecutable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Regla para compilar archivos .cc en .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc
	@mkdir -p $(dir $@) # Crear directorios necesarios en build
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar los archivos generados
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
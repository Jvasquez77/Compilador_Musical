# Makefile para el módulo de Análisis Semántico del Compilador Musical
# Compatible con clang++ -std=c++17

# Definir compilador y banderas
CXX = clang++ -std=c++17 -O0 -g
CXXFLAGS = -Wall -Wextra -pedantic -I. -I..

# Definir archivos objeto necesarios
AST_DIR = ../AST
OBJ = $(AST_DIR)/ast_node_interface.o $(AST_DIR)/datatype.o $(AST_DIR)/declaration.o $(AST_DIR)/expression.o $(AST_DIR)/statement.o symbol_table.o

# Target por defecto
all: demo_program

# Target principal: demo_program
demo_program: $(OBJ) demo_program.o
	$(CXX) $(CXXFLAGS) -o $@ $^

# Reglas de compilación para cada archivo objeto
demo_program.o: demo_program.cpp symbol_table.hpp $(AST_DIR)/ast_node_interface.hpp $(AST_DIR)/datatype.hpp $(AST_DIR)/declaration.hpp $(AST_DIR)/expression.hpp $(AST_DIR)/statement.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

symbol_table.o: symbol_table.cpp symbol_table.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Regla para compilar los objetos de AST (asumiendo que ya están compilados)
$(AST_DIR)/%.o:
	$(MAKE) -C $(AST_DIR) $(@F)

# Target para probar el análisis semántico (compila y ejecuta)
test: demo_program
	./demo_program

# Alias para test
run: test

# Target para limpiar archivos objeto y ejecutables
clean:
	rm -f *.o demo_program
	$(MAKE) -C $(AST_DIR) clean

# Declarar targets que no son archivos
.PHONY: all clean test run 
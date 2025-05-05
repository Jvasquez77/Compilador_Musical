# Makefile para el módulo AST del Compilador Musical
# Compatible con clang++ -std=c++17

# Definir compilador y banderas
CXX = clang++ -std=c++17
CC = clang
CXXFLAGS = -Wall -Wextra -pedantic -I.

# Definir archivos objeto necesarios
OBJ = ast_node_interface.o datatype.o declaration.o expression.o statement.o

# Target por defecto
all: demo_c_function

# Target principal: demo_c_function
demo_c_function: $(OBJ) demo_c_function.o
	$(CXX) $(CXXFLAGS) -o $@ $^

# Target para probar el AST (compila y ejecuta)
test: demo_c_function
	./demo_c_function

# Alias para test
run: test

# Reglas de compilación para cada archivo objeto
ast_node_interface.o: ast_node_interface.cpp ast_node_interface.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

datatype.o: datatype.cpp datatype.hpp ast_node_interface.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

declaration.o: declaration.cpp declaration.hpp datatype.hpp ast_node_interface.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

expression.o: expression.cpp expression.hpp datatype.hpp ast_node_interface.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

statement.o: statement.cpp statement.hpp expression.hpp ast_node_interface.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

demo_c_function.o: demo_c_function.cpp ast_node_interface.hpp datatype.hpp declaration.hpp expression.hpp statement.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Regla genérica para compilar archivos .cpp a .o (para cualquier otro archivo)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Target para limpiar archivos objeto y ejecutables
clean:
	rm -f *.o demo_c_function

# Declarar targets que no son archivos
.PHONY: all clean test run 
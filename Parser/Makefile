CXX = g++
CXXFLAGS = -std=c++17 -Wall -I.
FLEX = flex
BISON = bison

# Archivos objetivos
OBJECTS = scanner.o token.o expression.o main.o

# Nombre del ejecutable
TARGET = compilador_musical

all: $(TARGET)

# Regla para el objetivo principal
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Reglas para generar los archivos de Flex y Bison
scanner.cpp: scanner.flex token.h
	$(FLEX) -o $@ $<

token.cpp token.h: parser.bison expression.hpp
	$(BISON) --defines=token.h -o token.cpp $<

# Reglas para compilar archivos fuente
scanner.o: scanner.cpp token.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

token.o: token.cpp expression.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

expression.o: expression.cpp expression.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

main.o: main.cpp expression.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Regla para limpiar archivos generados
clean:
	rm -f $(TARGET) $(OBJECTS) scanner.cpp token.cpp token.h token.hpp token.h.bak token.tmp

# Regla para ejecutar pruebas
test_valid: $(TARGET)
	./$(TARGET) ../test/valid_test_01.mus

test_invalid: $(TARGET)
	./$(TARGET) ../test/invalid_test_01.mus

# Dependencias adicionales
token.o: expression.hpp

.PHONY: all clean test_valid test_invalid 
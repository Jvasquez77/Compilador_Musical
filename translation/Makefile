CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

OBJ = ../AST/ast_node_interface.o ../AST/declaration.o ../AST/expression.o ../AST/statement.o ../Semantic_Analysis/symbol_table.o

demo_translation: $(OBJ) demo_translation.cpp
	$(CXX) $(CXXFLAGS) -I.. -o $@ demo_translation.cpp $(OBJ)

clean:
	rm -f demo_translation *.o 
	rm -f ../AST/*.o ../Semantic_Analysis/*.o melodia.abc 
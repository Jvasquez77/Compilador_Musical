#include <iostream>
#include <cstdio>
#include <string>
#include "expression.hpp"

// Declaraciones externas para el parser y scanner
extern FILE* yyin;
extern int yyparse();
extern Expression* parser_result;

// Función para verificar la extensión del archivo
bool tiene_extension_mus(const std::string& nombre_archivo) {
    if (nombre_archivo.size() < 4) return false;
    return nombre_archivo.substr(nombre_archivo.size() - 4) == ".mus";
}

int main(int argc, char* argv[]) {
    // Verificar que se pasó un archivo como argumento
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <archivo.mus>" << std::endl;
        return 1;
    }

    std::string nombre_archivo = argv[1];

    // Verificar que el archivo tiene la extensión correcta
    if (!tiene_extension_mus(nombre_archivo)) {
        std::cerr << "Error: El archivo debe tener extensión .mus" << std::endl;
        return 1;
    }

    // Abrir el archivo de entrada
    yyin = fopen(nombre_archivo.c_str(), "r");
    if (!yyin) {
        std::cerr << "Error: No se pudo abrir el archivo " << nombre_archivo << std::endl;
        return 1;
    }

    std::cout << "Analizando archivo: " << nombre_archivo << std::endl;

    // Llamar al parser
    int resultado = yyparse();

    // Cerrar el archivo
    fclose(yyin);

    // Verificar el resultado del análisis
    if (resultado != 0 || parser_result == nullptr) {
        std::cerr << "Error: El análisis falló" << std::endl;
        return 1;
    }

    // Mostrar la representación en texto del programa
    std::cout << "\n--- Representación del programa ---\n" << std::endl;
    std::cout << parser_result->to_string() << std::endl;
    
    std::cout << "Análisis completado con éxito" << std::endl;

    // No tenemos que hacer nada con parser_result ya que se libera en el destructor del parser
    // Como medida de seguridad, establecemos el puntero a nullptr, pero no liberamos memoria
    parser_result = nullptr;

    return 0;
} 
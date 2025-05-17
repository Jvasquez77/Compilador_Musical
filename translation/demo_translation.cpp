/*
    Compilador Musical: Simulación de la traducción a ABC
    
    Este programa crea manualmente el AST que representaría el siguiente código musical 
    y ejecuta la traducción a ABC sobre él:

    Tempo 60
    Compas 7/8
    Tonalidad Si M

    Sol4 Corchea
    Sol4 Corchea
    La4 Corchea
    La4 Corchea
    Si4 Corchea
    Si4 Corchea
    Si4 Corchea

    Do#5 Corchea
    Do#5 Corchea
    Do#5 Corchea
    Re5 Corchea
    Re5 Corchea
    Mi5 Corchea
    Mi5 Corchea

    Fa#4 Negra
    Sol#4 Corchea
    La4 Corchea
    Si4 Negra
    Do#5 Semicorchea
*/

#include "../AST/declaration.hpp"
#include "../AST/statement.hpp"
#include "../AST/expression.hpp"
#include "../Semantic_Analysis/symbol_table.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>

// Función de demostración para crear y exportar a formato ABC
int main() {
    MusicProgram* program = new MusicProgram();
    
    // 1. Declaraciones
    // Tempo 60
    TempoDeclaration* tempo = new TempoDeclaration(60);
    program->add_declaration(tempo);
    
    // Compas 7/8
    TimeSignatureDeclaration* timeSignature = new TimeSignatureDeclaration(7, 8);
    program->add_declaration(timeSignature);
    
    // Tonalidad Si M
    KeyDeclaration* key = new KeyDeclaration("Si", KeyMode::MAYOR);
    program->add_declaration(key);
    
    // 2. Notas musicales
    // Patrón rítmico en 7/8 (2+2+3)
    program->add_statement(new NoteStatement(
        new NoteExpression("Sol", 4),
        new DurationExpression(DurationType::CORCHEA)
    ));
    program->add_statement(new NoteStatement(
        new NoteExpression("Sol", 4),
        new DurationExpression(DurationType::CORCHEA)
    ));
    program->add_statement(new NoteStatement(
        new NoteExpression("La", 4),
        new DurationExpression(DurationType::CORCHEA)
    ));
    program->add_statement(new NoteStatement(
        new NoteExpression("La", 4),
        new DurationExpression(DurationType::CORCHEA)
    ));
    program->add_statement(new NoteStatement(
        new NoteExpression("Si", 4),
        new DurationExpression(DurationType::CORCHEA)
    ));
    program->add_statement(new NoteStatement(
        new NoteExpression("Si", 4),
        new DurationExpression(DurationType::CORCHEA)
    ));
    program->add_statement(new NoteStatement(
        new NoteExpression("Si", 4),
        new DurationExpression(DurationType::CORCHEA)
    ));
    
    // Otro patrón rítmico (3+2+2)
    program->add_statement(new NoteStatement(
        new NoteExpression("Do#", 5),
        new DurationExpression(DurationType::CORCHEA)
    ));
    program->add_statement(new NoteStatement(
        new NoteExpression("Do#", 5),
        new DurationExpression(DurationType::CORCHEA)
    ));
    program->add_statement(new NoteStatement(
        new NoteExpression("Do#", 5),
        new DurationExpression(DurationType::CORCHEA)
    ));
    program->add_statement(new NoteStatement(
        new NoteExpression("Re", 5),
        new DurationExpression(DurationType::CORCHEA)
    ));
    program->add_statement(new NoteStatement(
        new NoteExpression("Re", 5),
        new DurationExpression(DurationType::CORCHEA)
    ));
    program->add_statement(new NoteStatement(
        new NoteExpression("Mi", 5),
        new DurationExpression(DurationType::CORCHEA)
    ));
    program->add_statement(new NoteStatement(
        new NoteExpression("Mi", 5),
        new DurationExpression(DurationType::CORCHEA)
    ));
    
    // Mezcla de duraciones
    program->add_statement(new NoteStatement(
        new NoteExpression("Fa#", 4),
        new DurationExpression(DurationType::NEGRA)
    ));
    program->add_statement(new NoteStatement(
        new NoteExpression("Sol#", 4),
        new DurationExpression(DurationType::CORCHEA)
    ));
    program->add_statement(new NoteStatement(
        new NoteExpression("La", 4),
        new DurationExpression(DurationType::CORCHEA)
    ));
    program->add_statement(new NoteStatement(
        new NoteExpression("Si", 4),
        new DurationExpression(DurationType::NEGRA)
    ));
    program->add_statement(new NoteStatement(
        new NoteExpression("Do#", 5),
        new DurationExpression(DurationType::SEMICORCHEA)
    ));
    
    // Validar el programa con análisis semántico
    SymbolTable symbolTable;
    bool isValid = program->resolve_names(symbolTable);
    
    if (isValid) {
        std::cout << "El programa es válido semánticamente.\n";
        
        // Abrir un archivo para escribir la notación ABC
        std::ofstream output("melodia.abc");
        if (output.is_open()) {
            double beat = 0.0;
            program->to_abc(output, beat);
            output.close();
            std::cout << "ABC written\n";
            
            // Mostrar el contenido del archivo ABC generado
            std::cout << "Contenido del archivo ABC generado:\n";
            std::cout << "-----------------------------------\n";
            std::ifstream abc_file("melodia.abc");
            if (abc_file.is_open()) {
                std::string line;
                while (getline(abc_file, line)) {
                    std::cout << line << '\n';
                }
                abc_file.close();
                std::cout << "-----------------------------------\n";
            }
        } else {
            std::cerr << "Error: No se pudo abrir el archivo.\n";
        }
    } else {
        std::cerr << "Error: El programa no es válido semánticamente.\n";
    }
    
    // Liberar memoria
    program->destroy();
    delete program;
    
    return 0;
} 
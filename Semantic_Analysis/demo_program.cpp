/*
    Compilador Musical: Simulación del Análisis Semántico
    
    Este programa crea manualmente el AST que representaría el siguiente código musical 
    y ejecuta el análisis semántico sobre él:

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

#include "../AST/ast_node_interface.hpp"
#include "../AST/datatype.hpp"
#include "../AST/declaration.hpp"
#include "../AST/expression.hpp"
#include "../AST/statement.hpp"
#include "symbol_table.hpp"
#include <iostream>
#include <string>

int main() {
    std::cout << "--- Iniciando programa de demostración del análisis semántico ---" << std::endl;
    
    // Crear un programa musical
    MusicProgram* program = new MusicProgram();
    
    // Agregar las declaraciones iniciales
    program->add_declaration(new TempoDeclaration(60));
    program->add_declaration(new TimeSignatureDeclaration(7, 8));
    program->add_declaration(new KeyDeclaration("Si", KeyMode::MAJOR));
    
    // Primer grupo rítmico
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
    
    // Segundo grupo rítmico
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
    
    // Tercer grupo - mezcla de duraciones
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
    
    // Análisis semántico
    std::cout << "--- Iniciando Análisis Semántico ---" << std::endl;
    
    SymbolTable symbol_table;
    bool semantic_result = program->resolve_names(symbol_table);
    
    if (semantic_result) {
        std::cout << "Análisis semántico completado con éxito. No se encontraron errores." << std::endl;
    } else {
        std::cout << "Se encontraron errores en el análisis semántico." << std::endl;
    }
    
    // Imprimir el AST
    std::cout << "\n--- AST del Programa Musical ---" << std::endl;
    std::cout << program->to_string() << std::endl;
    
    return 0;
} 
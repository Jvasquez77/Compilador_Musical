/*
    Compilador Musical: Simulación del Árbol de Sintaxis Abstracta (AST)

    Este programa crea manualmente el AST que representaría el siguiente código musical:

    Tempo 60
    Compas 7/8
    Tonalidad Si M

    // Patrones rítmicos en 7/8 (agrupados 2+2+3)
    Sol4 Corchea
    Sol4 Corchea
    La4 Corchea
    La4 Corchea
    Si4 Corchea
    Si4 Corchea
    Si4 Corchea

    // Otro patrón rítmico (3+2+2)
    Do#5 Corchea
    Do#5 Corchea
    Do#5 Corchea
    Re5 Corchea
    Re5 Corchea
    Mi5 Corchea
    Mi5 Corchea

    // Mezcla de duraciones
    Fa#4 Negra
    Sol#4 Corchea
    La4 Corchea
    Si4 Negra
    Do#5 Semicorchea
*/

#include "ast_node_interface.hpp"
#include "declaration.hpp"
#include "expression.hpp"
#include "statement.hpp"
#include "../Semantic_Analysis/symbol_table.hpp"
#include <iostream>
#include <string>

// Clase Program para simular un programa musical completo
class Program : public ASTNodeInterface {
public:
    // Constructor
    Program() noexcept = default;

    // Agregar una declaración (Tempo, Compas, Tonalidad)
    void add_declaration(Declaration* decl) noexcept {
        declarations.push_front(decl);
    }

    // Agregar una nota
    void add_statement(Statement* stmt) noexcept {
        statements.push_front(stmt);
    }

    // Representación en string del programa completo
    std::string to_string() const noexcept override {
        std::string result;

        // Imprimir declaraciones en orden inverso (porque las agregamos al frente)
        std::forward_list<Declaration*> reversed_decls;
        for (auto decl : declarations) {
            reversed_decls.push_front(decl);
        }
        for (auto decl : reversed_decls) {
            result += decl->to_string() + "\n";
        }

        // Separador entre declaraciones y notas
        if (!declarations.empty() && !statements.empty()) {
            result += "\n";
        }

        // Imprimir notas en orden inverso 
        std::forward_list<Statement*> reversed_stmts;
        for (auto stmt : statements) {
            reversed_stmts.push_front(stmt);
        }
        for (auto stmt : reversed_stmts) {
            result += stmt->to_string() + "\n";
        }

        return result;
    }

    // Liberar memoria
    void destroy() noexcept override {
        // Destruir todas las declaraciones
        while (!declarations.empty()) {
            auto decl = declarations.front();
            declarations.pop_front();
            if (decl) {
                decl->destroy();
                delete decl;
            }
        }

        // Destruir todas las notas
        while (!statements.empty()) {
            auto stmt = statements.front();
            statements.pop_front();
            if (stmt) {
                stmt->destroy();
                delete stmt;
            }
        }
    }

    // Implementación del método resolve_names
    bool resolve_names(SymbolTable& table) noexcept override {
        bool result = true;
        
        // Entrar en un nuevo ámbito
        table.enter_scope();
        
        // Resolver nombres en todas las declaraciones
        for (auto decl : declarations) {
            if (decl && !decl->resolve_names(table)) {
                result = false;
            }
        }
        
        // Resolver nombres en todos los statements
        for (auto stmt : statements) {
            if (stmt && !stmt->resolve_names(table)) {
                result = false;
            }
        }
        
        // Salir del ámbito
        table.exit_scope();
        
        return result;
    }

private:
    std::forward_list<Declaration*> declarations;
    std::forward_list<Statement*> statements;
};

int main() {
    // Crear un programa musical
    Program program;
    
    // Agregar las declaraciones iniciales
    program.add_declaration(new TempoDeclaration(60));
    program.add_declaration(new TimeSignatureDeclaration(7, 8));
    program.add_declaration(new KeyDeclaration("Si", KeyMode::MAYOR));
    
    // Primer patrón rítmico (2+2+3)
    program.add_statement(new NoteStatement(
        new NoteExpression("Sol", 4),
        new DurationExpression(DurationType::CORCHEA)
    ));
    
    program.add_statement(new NoteStatement(
        new NoteExpression("Sol", 4),
        new DurationExpression(DurationType::CORCHEA)
    ));
    
    program.add_statement(new NoteStatement(
        new NoteExpression("La", 4),
        new DurationExpression(DurationType::CORCHEA)
    ));
    
    program.add_statement(new NoteStatement(
        new NoteExpression("La", 4),
        new DurationExpression(DurationType::CORCHEA)
    ));
    
    program.add_statement(new NoteStatement(
        new NoteExpression("Si", 4),
        new DurationExpression(DurationType::CORCHEA)
    ));
    
    program.add_statement(new NoteStatement(
        new NoteExpression("Si", 4),
        new DurationExpression(DurationType::CORCHEA)
    ));
    
    program.add_statement(new NoteStatement(
        new NoteExpression("Si", 4),
        new DurationExpression(DurationType::CORCHEA)
    ));
    
    // Segundo patrón rítmico (3+2+2)
    program.add_statement(new NoteStatement(
        new NoteExpression("Do#", 5),
        new DurationExpression(DurationType::CORCHEA)
    ));
    
    program.add_statement(new NoteStatement(
        new NoteExpression("Do#", 5),
        new DurationExpression(DurationType::CORCHEA)
    ));
    
    program.add_statement(new NoteStatement(
        new NoteExpression("Do#", 5),
        new DurationExpression(DurationType::CORCHEA)
    ));
    
    program.add_statement(new NoteStatement(
        new NoteExpression("Re", 5),
        new DurationExpression(DurationType::CORCHEA)
    ));
    
    program.add_statement(new NoteStatement(
        new NoteExpression("Re", 5),
        new DurationExpression(DurationType::CORCHEA)
    ));
    
    program.add_statement(new NoteStatement(
        new NoteExpression("Mi", 5),
        new DurationExpression(DurationType::CORCHEA)
    ));
    
    program.add_statement(new NoteStatement(
        new NoteExpression("Mi", 5),
        new DurationExpression(DurationType::CORCHEA)
    ));
    
    // Mezcla de duraciones
    program.add_statement(new NoteStatement(
        new NoteExpression("Fa#", 4),
        new DurationExpression(DurationType::NEGRA)
    ));
    
    program.add_statement(new NoteStatement(
        new NoteExpression("Sol#", 4),
        new DurationExpression(DurationType::CORCHEA)
    ));
    
    program.add_statement(new NoteStatement(
        new NoteExpression("La", 4),
        new DurationExpression(DurationType::CORCHEA)
    ));
    
    program.add_statement(new NoteStatement(
        new NoteExpression("Si", 4),
        new DurationExpression(DurationType::NEGRA)
    ));
    
    program.add_statement(new NoteStatement(
        new NoteExpression("Do#", 5),
        new DurationExpression(DurationType::SEMICORCHEA)
    ));
    
    // Imprimir el AST simulado
    std::cout << "--- AST Simulado del Programa Musical ---" << std::endl;
    std::cout << program.to_string() << std::endl;
    
    // Liberar toda la memoria
    program.destroy();
    
    return 0;
} 
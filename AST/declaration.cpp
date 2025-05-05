#include "declaration.hpp"
#include "statement.hpp"
#include "../Semantic_Analysis/symbol_table.hpp"
#include <vector>
#include <iostream>

// TempoDeclaration implementacion
TempoDeclaration::TempoDeclaration(int tempo_value) noexcept
    : tempo{new Tempo(tempo_value)} {}

int TempoDeclaration::get_tempo_value() const noexcept {
    return tempo->get_bpm();
}

DataType TempoDeclaration::get_declaration_type() const noexcept {
    return DataType::TEMPO;
}

std::string TempoDeclaration::to_string() const noexcept {
    return "Tempo " + std::to_string(tempo->get_bpm());
}

void TempoDeclaration::destroy() noexcept {
    if (tempo != nullptr) {
        tempo->destroy();
        delete tempo;
        tempo = nullptr;
    }
}

// Implementación del método resolve_names para TempoDeclaration
bool TempoDeclaration::resolve_names(SymbolTable& table) noexcept{
    if (table.contains("__tempo__"))
    {
        std::cerr << "Error: Tempo declarado más de una vez.\n";
        return false;
    }
    
    if (this->tempo->get_bpm() <= 0)
    {
        std::cerr << "Error: El tempo debe ser positivo.\n";
        return false;
    }
    
    table.insert("__tempo__", DataType::TEMPO);
    return true;
}

// implementacion de la declaracion de compas
TimeSignatureDeclaration::TimeSignatureDeclaration(int numerator, int denominator) noexcept
    : time_signature{new TimeSignature(numerator, denominator)} {}

int TimeSignatureDeclaration::get_numerator() const noexcept {
    return time_signature->get_numerator();
}

int TimeSignatureDeclaration::get_denominator() const noexcept {
    return time_signature->get_denominator();
}

DataType TimeSignatureDeclaration::get_declaration_type() const noexcept {
    return DataType::TIME_SIGNATURE;
}

std::string TimeSignatureDeclaration::to_string() const noexcept {
    return "Compas " + time_signature->to_string();
}

void TimeSignatureDeclaration::destroy() noexcept {
    if (time_signature != nullptr) {
        time_signature->destroy();
        delete time_signature;
        time_signature = nullptr;
    }
}

// Implementación del método resolve_names para TimeSignatureDeclaration
bool TimeSignatureDeclaration::resolve_names(SymbolTable& table) noexcept{
    if (table.contains("__time_signature__"))
    {
        std::cerr << "Error: Compás declarado más de una vez.\n";
        return false;
    }
    
    int numerator = this->time_signature->get_numerator();
    int denominator = this->time_signature->get_denominator();
    
    if (numerator <= 0)
    {
        std::cerr << "Error: El numerador del compás debe ser positivo.\n";
        return false;
    }
    
    if (denominator != 2 && denominator != 4 && denominator != 8 && denominator != 16)
    {
        std::cerr << "Error: El denominador del compás debe ser 2, 4, 8 o 16.\n";
        return false;
    }
    
    table.insert("__time_signature__", DataType::TIME_SIGNATURE);
    return true;
}

// implementacion de la declaracion de clave (tonalidad)
KeyDeclaration::KeyDeclaration(const std::string& root_note, KeyMode mode) noexcept
    : key{new Key(root_note, mode)} {}

std::string KeyDeclaration::get_root_note() const noexcept {
    return key->get_root_note();
}

KeyMode KeyDeclaration::get_mode() const noexcept {
    return key->get_mode();
}

DataType KeyDeclaration::get_declaration_type() const noexcept {
    return DataType::KEY;
}

std::string KeyDeclaration::to_string() const noexcept {
    return "Tonalidad " + key->to_string();
}

void KeyDeclaration::destroy() noexcept {
    if (key != nullptr) {
        key->destroy();
        delete key;
        key = nullptr;
    }
}

// Implementación del método resolve_names para KeyDeclaration
bool KeyDeclaration::resolve_names(SymbolTable& table) noexcept{
    if (table.contains("__key__"))
    {
        std::cerr << "Error: Tonalidad declarada más de una vez.\n";
        return false;
    }
    
    // Verificar que la nota raíz sea válida
    std::string root = this->key->get_root_note();
    // Lista de notas musicales válidas
    std::vector<std::string> valid_notes = {"Do", "Re", "Mi", "Fa", "Sol", "La", "Si", "Do#", "Re#", "Fa#", "Sol#", "La#", "Reb", "Mib", "Solb", "Lab", "Sib"};
    
    bool valid_root = false;
    for (const auto& note : valid_notes)
    {
        if (root == note)
        {
            valid_root = true;
            break;
        }
    }
    
    if (!valid_root)
    {
        std::cerr << "Error: Nota raíz inválida: " << root << ".\n";
        return false;
    }
    
    table.insert("__key__", DataType::KEY);
    return true;
}

// Implementación de la clase MusicProgram
MusicProgram::MusicProgram() noexcept{
    // No hay inicialización especial necesaria
}

MusicProgram::~MusicProgram() noexcept{
    this->destroy();
}

void MusicProgram::add_declaration(Declaration* declaration) noexcept{
    if (declaration != nullptr)
    {
        this->declarations.push_back(declaration);
    }
}

void MusicProgram::add_statement(Statement* statement) noexcept{
    if (statement != nullptr)
    {
        this->statements.push_back(statement);
    }
}

const std::vector<Declaration*>& MusicProgram::get_declarations() const noexcept{
    return this->declarations;
}

const std::vector<Statement*>& MusicProgram::get_statements() const noexcept{
    return this->statements;
}

std::string MusicProgram::to_string() const noexcept{
    std::string result = "Programa Musical:\n";
    
    // Agregar todas las declaraciones
    result += "Declaraciones:\n";
    for (const auto& decl : this->declarations)
    {
        result += "  " + decl->to_string() + "\n";
    }
    
    // Agregar todos los statements
    result += "Notas:\n";
    for (const auto& stmt : this->statements)
    {
        result += "  " + stmt->to_string() + "\n";
    }
    
    return result;
}

void MusicProgram::destroy() noexcept{
    // Destruir todas las declaraciones
    for (auto decl : this->declarations)
    {
        if (decl != nullptr)
        {
            decl->destroy();
        }
    }
    this->declarations.clear();
    
    // Destruir todos los statements
    for (auto stmt : this->statements)
    {
        if (stmt != nullptr)
        {
            stmt->destroy();
        }
    }
    this->statements.clear();
    
    delete this;
}

bool MusicProgram::resolve_names(SymbolTable& table) noexcept{
    // Resolver nombres en todas las declaraciones
    for (auto decl : this->declarations)
    {
        if (!decl->resolve_names(table))
        {
            std::cerr << "Error en la resolución de nombres para la declaración: " 
                     << decl->to_string() << "\n";
            return false;
        }
    }
    
    // resolver nombres en todos los statements
    for (auto stmt : this->statements)
    {
        if (!stmt->resolve_names(table))
        {
            std::cerr << "Error en la resolución de nombres para el statement: " 
                     << stmt->to_string() << "\n";
            return false;
        }
    }
    
    return true;
} 
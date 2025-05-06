#include "expression.hpp"
#include "../Semantic_Analysis/symbol_table.hpp"
#include <iostream>
#include <vector>

// implementacion de NoteExpression 
NoteExpression::NoteExpression(const std::string& note_name, int octave) noexcept
    : note_name{note_name}, octave{octave} {}

std::string NoteExpression::get_note_name() const noexcept {
    return note_name;
}

int NoteExpression::get_octave() const noexcept {
    return octave;
}

std::string NoteExpression::to_string() const noexcept {
    return note_name + std::to_string(octave);
}

void NoteExpression::destroy() noexcept {
    // No hay memoria que liberar
}

// implementacion de DurationExpression 
DurationExpression::DurationExpression(DurationType type) noexcept
    : duration_type{type} {}

DurationType DurationExpression::get_duration_type() const noexcept {
    return duration_type;
}

std::string DurationExpression::to_string() const noexcept {
    switch (duration_type) {
        case DurationType::SEMICORCHEA: return "Semicorchea";
        case DurationType::CORCHEA: return "Corchea";
        case DurationType::NEGRA: return "Negra";
        case DurationType::BLANCA: return "Blanca";
        default: return "Unknown";
    }
}

void DurationExpression::destroy() noexcept {
 
}

// implementacion del metodo resolve_names (verificacion semantica) para NoteExpression
bool NoteExpression::resolve_names(SymbolTable& table) noexcept{
    // Verificar que la nota sea válida
    std::vector<std::string> valid_notes = {"Do", "Re", "Mi", "Fa", "Sol", "La", "Si", 
                                          "Do#", "Re#", "Fa#", "Sol#", "La#", "Si#",
                                          "Dob", "Reb", "Mib", "Solb", "Lab", "Sib",
                                          "C", "D", "E", "F", "G", "A", "B",
                                          "Cb", "Db", "Eb", "Gb", "Ab", "Bb",
                                          "C#", "D#", "F#", "G#", "A#", "B#"
                                          };
    
    bool valid_note = false;
    for (const auto& note : valid_notes)
    {
        if (note_name == note)
        {
            valid_note = true;
            break;
        }
    }
    
    if (!valid_note)
    {
        std::cerr << "Error: Nota inválida: " << note_name << ".\n";
        return false;
    }
    
    // Verificar que la octava esté en un rango válido (1-8)
    if (octave < 1 || octave > 8)
    {
        std::cerr << "Error: Octava fuera de rango (1-8): " << octave << ".\n";
        return false;
    }
    
    return true;
}

// implementacion del metodo resolve_names (verificacion semantica) para DurationExpression
bool DurationExpression::resolve_names(SymbolTable& /*table*/) noexcept{
    // Todas las duraciones son válidas porque están definidas como enum
    return true;
} 
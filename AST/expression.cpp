#include "expression.hpp"
#include "../Semantic_Analysis/symbol_table.hpp"
#include <iostream>
#include <vector>

// implementacion de NoteExpression 
NoteExpression::NoteExpression(const std::string& note_name, int octave) noexcept
    : note{new Note(note_name, octave)} {}

std::string NoteExpression::get_note_name() const noexcept {
    return note->get_note_name();
}

int NoteExpression::get_octave() const noexcept {
    return note->get_octave();
}

DataType NoteExpression::get_expression_type() const noexcept {
    return DataType::NOTE;
}

std::string NoteExpression::to_string() const noexcept {
    return note->to_string();
}

void NoteExpression::destroy() noexcept {
    if (note != nullptr) {
        note->destroy();
        delete note;
        note = nullptr;
    }
}

// implementacion de DurationExpression 
DurationExpression::DurationExpression(DurationType type) noexcept
    : duration{new Duration(type)} {}

DurationType DurationExpression::get_duration_type() const noexcept {
    return duration->get_duration_type();
}

DataType DurationExpression::get_expression_type() const noexcept {
    return DataType::DURATION;
}

std::string DurationExpression::to_string() const noexcept {
    return duration->to_string();
}

void DurationExpression::destroy() noexcept {
    if (duration != nullptr) {
        duration->destroy();
        delete duration;
        duration = nullptr;
    }
}

// implementacion del metodo resolve_names para NoteExpression
bool NoteExpression::resolve_names(SymbolTable& table) noexcept{
    // Verificar que la nota sea válida
    std::string note_name = this->note->get_note_name();
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
    int octave = this->note->get_octave();
    if (octave < 1 || octave > 8)
    {
        std::cerr << "Error: Octava fuera de rango (1-8): " << octave << ".\n";
        return false;
    }
    
    return true;
}
// implementacion del metodo resolve_names para DurationExpression
bool DurationExpression::resolve_names(SymbolTable& table) noexcept{
    // Todas las duraciones son válidas porque están definidas como enum
    return true;
} 
#include "statement.hpp"

// Implementacion de NoteStatement 
NoteStatement::NoteStatement(NoteExpression* note, DurationExpression* duration) noexcept
    : note{note}, duration{duration} {}

NoteExpression* NoteStatement::get_note() const noexcept {
    return note;
}

DurationExpression* NoteStatement::get_duration() const noexcept {
    return duration;
}

std::string NoteStatement::to_string() const noexcept {
    return note->to_string() + " " + duration->to_string();
}

void NoteStatement::destroy() noexcept {
    if (note != nullptr) {
        note->destroy();
        delete note;
    }
    
    if (duration != nullptr) {
        duration->destroy();
        delete duration;
    }
} 
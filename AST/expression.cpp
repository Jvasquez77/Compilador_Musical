#include "expression.hpp"

// NoteExpression implementation
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

// DurationExpression implementation
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
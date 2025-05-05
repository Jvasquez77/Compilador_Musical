#include "datatype.hpp"
#include "../Semantic_Analysis/symbol_table.hpp"

// implementacion de duracion
Duration::Duration(DurationType type) noexcept
    : duration_type{type} {}

DurationType Duration::get_duration_type() const noexcept {
    return duration_type;
}

DataType Duration::get_type() const noexcept {
    return DataType::DURATION;
}

std::string Duration::to_string() const noexcept {
    switch (duration_type) {
        case DurationType::SEMICORCHEA: return "Semicorchea";
        case DurationType::CORCHEA: return "Corchea";
        case DurationType::NEGRA: return "Negra";
        case DurationType::BLANCA: return "Blanca";
        default: return "Unknown";
    }
}

void Duration::destroy() noexcept {
    
}

bool Duration::resolve_names(SymbolTable& /*table*/) noexcept {
    return true; // Los tipos de datos no necesitan resolver nombres
}

// implementacion de la clave (tonalidad)
Key::Key(const std::string& root_note, KeyMode mode) noexcept
    : root_note{root_note}, mode{mode} {}

std::string Key::get_root_note() const noexcept {
    return root_note;
}

KeyMode Key::get_mode() const noexcept {
    return mode;
}

DataType Key::get_type() const noexcept {
    return DataType::KEY;
}

std::string Key::to_string() const noexcept {
    std::string mode_str = (mode == KeyMode::MAYOR) ? "M" : "m";
    return root_note + " " + mode_str;
}

void Key::destroy() noexcept {
    
}

bool Key::resolve_names(SymbolTable& /*table*/) noexcept {
    return true; // Los tipos de datos no necesitan resolver nombres
}

// implementacion de la nota
Note::Note(const std::string& note_name, int octave) noexcept
    : note_name{note_name}, octave{octave} {}

std::string Note::get_note_name() const noexcept {
    return note_name;
}

int Note::get_octave() const noexcept {
    return octave;
}

DataType Note::get_type() const noexcept {
    return DataType::NOTE;
}

std::string Note::to_string() const noexcept {
    return note_name + std::to_string(octave);
}

void Note::destroy() noexcept {
    
}

bool Note::resolve_names(SymbolTable& /*table*/) noexcept {
    return true; // Los tipos de datos no necesitan resolver nombres
}

// implementacion del tempo
Tempo::Tempo(int bpm) noexcept
    : bpm{bpm} {}

int Tempo::get_bpm() const noexcept {
    return bpm;
}

DataType Tempo::get_type() const noexcept {
    return DataType::TEMPO;
}

std::string Tempo::to_string() const noexcept {
    return std::to_string(bpm) + " BPM";
}

void Tempo::destroy() noexcept {
    
}

bool Tempo::resolve_names(SymbolTable& /*table*/) noexcept {
    return true; // Los tipos de datos no necesitan resolver nombres
}

// implementacion del compás
TimeSignature::TimeSignature(int numerator, int denominator) noexcept
    : numerator{numerator}, denominator{denominator} {}

int TimeSignature::get_numerator() const noexcept {
    return numerator;
}

int TimeSignature::get_denominator() const noexcept {
    return denominator;
}

DataType TimeSignature::get_type() const noexcept {
    return DataType::TIME_SIGNATURE;
}

std::string TimeSignature::to_string() const noexcept {
    return std::to_string(numerator) + "/" + std::to_string(denominator);
}

void TimeSignature::destroy() noexcept {
    
}

bool TimeSignature::resolve_names(SymbolTable& /*table*/) noexcept {
    return true; // Los tipos de datos no necesitan resolver nombres
} 
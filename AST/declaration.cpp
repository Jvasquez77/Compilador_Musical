#include "declaration.hpp"

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
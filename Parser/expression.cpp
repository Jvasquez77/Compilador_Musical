#include "expression.hpp"
#include <sstream>

using namespace std::literals;

Expression::~Expression() {}

// Implementación de Number
Number::Number(int val) noexcept
    : value{val} {}

void Number::destroy() noexcept {
    delete this;
}

std::string Number::to_string() const noexcept {
    return std::to_string(value);
}

// Implementación de Tempo
Tempo::Tempo(Number* val) noexcept
    : tempo_value{val} {}

void Tempo::destroy() noexcept {
    if (tempo_value != nullptr) {
        tempo_value->destroy();
        tempo_value = nullptr;
    }
    delete this;
}

std::string Tempo::to_string() const noexcept {
    return "Tempo "s + tempo_value->to_string();
}

int Tempo::getTempo() const noexcept {
    return tempo_value->getIntValue();
}

// Implementación de TimeSignature
TimeSignature::TimeSignature(Number* num, Number* denom) noexcept
    : numerator{num}, denominator{denom} {}

void TimeSignature::destroy() noexcept {
    if (numerator != nullptr) {
        numerator->destroy();
        numerator = nullptr;
    }
    if (denominator != nullptr) {
        denominator->destroy();
        denominator = nullptr;
    }
    delete this;
}

std::string TimeSignature::to_string() const noexcept {
    return "Compas "s + numerator->to_string() + "/"s + denominator->to_string();
}

int TimeSignature::getNumerator() const noexcept {
    return numerator->getIntValue();
}

int TimeSignature::getDenominator() const noexcept {
    return denominator->getIntValue();
}

// Implementación de Key
Key::Key(std::string note_name, KeyType type) noexcept
    : note{note_name}, key_type{type} {}

void Key::destroy() noexcept {
    delete this;
}

std::string Key::to_string() const noexcept {
    std::string type_str = (key_type == KeyType::MAJOR) ? "M" : "m";
    return "Tonalidad "s + note + " "s + type_str;
}

std::string Key::getNote() const noexcept {
    return note;
}

Key::KeyType Key::getType() const noexcept {
    return key_type;
}

// Implementación de Note
Note::Note(std::string note_name, int oct, Duration dur) noexcept
    : note_name{note_name}, octave{oct}, duration{dur} {}

void Note::destroy() noexcept {
    delete this;
}

std::string Note::to_string() const noexcept {
    return note_name + std::to_string(octave) + " "s + durationToString(duration);
}

std::string Note::getNoteName() const noexcept {
    return note_name;
}

int Note::getOctave() const noexcept {
    return octave;
}

Duration Note::getDuration() const noexcept {
    return duration;
}

// Implementación de Program
Program::Program() noexcept {}

Program::~Program() {
    destroy();
}

void Program::destroy() noexcept {
    for (auto instruction : instructions) {
        if (instruction != nullptr) {
            instruction->destroy();
        }
    }
    instructions.clear();
    delete this;
}

std::string Program::to_string() const noexcept {
    std::stringstream ss;
    for (const auto& instruction : instructions) {
        if (instruction != nullptr) {
            ss << instruction->to_string() << "\n";
        }
    }
    return ss.str();
}

void Program::addInstruction(Expression* instruction) noexcept {
    if (instruction != nullptr) {
        instructions.push_back(instruction);
    }
}

const std::vector<Expression*>& Program::getInstructions() const noexcept {
    return instructions;
}

// Implementación de la función durationToString
std::string durationToString(Duration duration) noexcept {
    switch (duration) {
        case Duration::BLANCA:
            return "Blanca";
        case Duration::NEGRA:
            return "Negra";
        case Duration::CORCHEA:
            return "Corchea";
        case Duration::SEMICORCHEA:
            return "Semicorchea";
        default:
            return "Desconocido";
    }
} 
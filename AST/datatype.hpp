#pragma once

#include <string>

// Forward declaration
class ASTNodeInterface;

enum class DataType {
    NOTE,          // Representa la nota musical (Do, Re, Mi, etc.)
    DURATION,       // Representa la duración de una nota (redonda, blanca, negra, etc.)
    TEMPO,          // Representa la velocidad de ejecución de la pieza musical
    TIME_SIGNATURE, // Representa el compás o medida (4/4, 3/4, etc.)
    KEY             // Representa la tonalidad de la pieza musical (Do mayor, La menor, etc.)
};

class Datatype
{
public:
    virtual ~Datatype() noexcept = default;
    virtual DataType get_type() const noexcept = 0;
    virtual std::string to_string() const noexcept = 0;
    virtual void destroy() noexcept = 0;
};

enum class DurationType {
    SEMICORCHEA,   // Semicorchea
    CORCHEA,       // Corchea
    NEGRA,         // Negra
    BLANCA         // Blanca
};

class Duration : public Datatype
{
public:
    Duration(DurationType type) noexcept;

    DurationType get_duration_type() const noexcept;
    DataType get_type() const noexcept override;
    std::string to_string() const noexcept override;
    void destroy() noexcept override;

private:
    DurationType duration_type;
};

enum class KeyMode {
    MAJOR,  // Mayor
    MINOR   // Menor
};

class Key : public Datatype
{
public:
    Key(const std::string& root_note, KeyMode mode) noexcept;

    std::string get_root_note() const noexcept;
    KeyMode get_mode() const noexcept;
    DataType get_type() const noexcept override;
    std::string to_string() const noexcept override;
    void destroy() noexcept override;

private:
    std::string root_note;
    KeyMode mode;
};

class Note : public Datatype
{
public:
    Note(const std::string& note_name, int octave) noexcept;

    std::string get_note_name() const noexcept;
    int get_octave() const noexcept;
    DataType get_type() const noexcept override;
    std::string to_string() const noexcept override;
    void destroy() noexcept override;

private:
    std::string note_name;  // Alteraciones (e.g., "Do#", "Sib")
    int octave;
};

class Tempo : public Datatype
{
public:
    Tempo(int bpm) noexcept;

    int get_bpm() const noexcept;
    DataType get_type() const noexcept override;
    std::string to_string() const noexcept override;
    void destroy() noexcept override;

private:
    int bpm;  
};

class TimeSignature : public Datatype // Representa el compás (4/4, 3/4, etc.)
{
public:
    TimeSignature(int numerator, int denominator) noexcept;

    int get_numerator() const noexcept;
    int get_denominator() const noexcept;
    DataType get_type() const noexcept override;
    std::string to_string() const noexcept override;
    void destroy() noexcept override;

private:
    int numerator;    // Número de pulsos por compás
    int denominator;  // Figura que recibe un pulso
}; 
#pragma once

#include <string>
#include <vector>

class Expression;

// Clase base para todas las expresiones musicales
class Expression {
public:
    virtual ~Expression();
    virtual void destroy() noexcept = 0;
    virtual std::string to_string() const noexcept = 0;
    
    virtual std::string getStringValue() const noexcept {//acceso a valor string
        return ""; 
    }
    
    virtual int getIntValue() const noexcept {
        return 0;
    }
    
    virtual void addInstruction(Expression* instruction) noexcept {
    }
};

// Clase para representar un valor numérico
class Number : public Expression {
public:
    Number(int val) noexcept;
    void destroy() noexcept override;
    std::string to_string() const noexcept override;
    
    int getIntValue() const noexcept override {
        return value;
    }

private:
    int value;
};

// Clase para representar un valor string
class StringExpression : public Expression {
public:
    StringExpression(const std::string& val) noexcept : value(val) {}
    void destroy() noexcept override {
        delete this;
    }
    std::string to_string() const noexcept override {
        return value;
    }
    
    std::string getStringValue() const noexcept override {
        return value;
    }

private:
    std::string value;
};

// Clase para el tempo
class Tempo : public Expression {
public:
    Tempo(Number* val) noexcept;
    void destroy() noexcept override;
    std::string to_string() const noexcept override;
    int getTempo() const noexcept;

private:
    Number* tempo_value;
};

// Clase para el compás
class TimeSignature : public Expression {
public:
    TimeSignature(Number* numerator, Number* denominator) noexcept;
    void destroy() noexcept override;
    std::string to_string() const noexcept override;
    int getNumerator() const noexcept;
    int getDenominator() const noexcept;

private:
    Number* numerator;
    Number* denominator;
};

// Clase para la tonalidad
class Key : public Expression {
public:
    enum class KeyType { MAJOR, MINOR };
    
    Key(std::string note, KeyType type) noexcept;
    void destroy() noexcept override;
    std::string to_string() const noexcept override;
    std::string getNote() const noexcept;
    KeyType getType() const noexcept;

private:
    std::string note;
    KeyType key_type;
};

// Enumeración para las duraciones de las notas
enum class Duration {
    BLANCA,
    NEGRA,
    CORCHEA,
    SEMICORCHEA
};

// Clase para representar una nota musical
class Note : public Expression {
public:
    Note(std::string note_name, int octave, Duration duration) noexcept;
    void destroy() noexcept override;
    std::string to_string() const noexcept override;
    std::string getNoteName() const noexcept;
    int getOctave() const noexcept;
    Duration getDuration() const noexcept;

private:
    std::string note_name;
    int octave;
    Duration duration;
};

// Clase para almacenar y manejar una secuencia de instrucciones musicales
class Program : public Expression {
public:
    Program() noexcept;
    ~Program();
    void destroy() noexcept override;
    std::string to_string() const noexcept override;
    void addInstruction(Expression* instruction) noexcept override;
    const std::vector<Expression*>& getInstructions() const noexcept;

private:
    std::vector<Expression*> instructions;
};

// Función para convertir una duración a string
std::string durationToString(Duration duration) noexcept; 
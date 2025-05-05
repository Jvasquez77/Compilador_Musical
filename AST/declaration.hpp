#pragma once

#include "ast_node_interface.hpp"
#include "datatype.hpp"
#include <string>

class Declaration : public ASTNodeInterface
{
public:
    virtual DataType get_declaration_type() const noexcept = 0;
};
//declaracion de tempo
class TempoDeclaration : public Declaration
{
public:
    TempoDeclaration(int tempo_value) noexcept;

    int get_tempo_value() const noexcept;
    DataType get_declaration_type() const noexcept override;
    std::string to_string() const noexcept override;
    void destroy() noexcept override;

private:
    Tempo* tempo;
};
//declaracion de compas
class TimeSignatureDeclaration : public Declaration
{
public:
    TimeSignatureDeclaration(int numerator, int denominator) noexcept;

    int get_numerator() const noexcept;
    int get_denominator() const noexcept;
    DataType get_declaration_type() const noexcept override;
    std::string to_string() const noexcept override;
    void destroy() noexcept override;

private:
    TimeSignature* time_signature;
};
//declaracion de clave (tonalidad)
class KeyDeclaration : public Declaration
{
public:
    KeyDeclaration(const std::string& root_note, KeyMode mode) noexcept;

    std::string get_root_note() const noexcept;
    KeyMode get_mode() const noexcept;
    DataType get_declaration_type() const noexcept override;
    std::string to_string() const noexcept override;
    void destroy() noexcept override;

private:
    Key* key;
}; 
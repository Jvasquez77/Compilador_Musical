#pragma once

#include "ast_node_interface.hpp"
#include "datatype.hpp"
#include <string>

class Expression : public ASTNodeInterface
{
public:
    virtual DataType get_expression_type() const noexcept = 0;
};

class NoteExpression : public Expression
{
public:
    NoteExpression(const std::string& note_name, int octave) noexcept;

    std::string get_note_name() const noexcept;
    int get_octave() const noexcept;
    DataType get_expression_type() const noexcept override;
    std::string to_string() const noexcept override;
    void destroy() noexcept override;

private:
    Note* note;
};

class DurationExpression : public Expression
{
public:
    DurationExpression(DurationType type) noexcept;

    DurationType get_duration_type() const noexcept;
    DataType get_expression_type() const noexcept override;
    std::string to_string() const noexcept override;
    void destroy() noexcept override;

private:
    Duration* duration;
}; 
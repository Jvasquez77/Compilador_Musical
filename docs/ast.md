# Documentación del Árbol de Sintaxis Abstracta (AST) para Lenguaje Musical

## Introducción

Este documento describe la implementación del Árbol de Sintaxis Abstracta (AST) para el compilador de lenguaje musical. El AST proporciona una representación estructurada y jerárquica del código fuente musical después del análisis sintáctico, facilitando su posterior análisis semántico y generación de código.

## Arquitectura del AST

El sistema está organizado mediante una jerarquía de clases C++ que representan los distintos elementos del lenguaje musical.

### Interfaz Base

Todos los nodos del AST implementan una interfaz común definida en `ast_node_interface.hpp`:

```cpp
class ASTNodeInterface {
public:
    virtual ~ASTNodeInterface() noexcept = default;
    virtual void destroy() noexcept = 0;
    virtual std::string to_string() const noexcept = 0;
    virtual bool resolve_names(SymbolTable& table) noexcept = 0;
};
```

Esta interfaz proporciona:
- Un destructor virtual para permitir la destrucción polimórfica
- Un método `destroy()` para la liberación manual de recursos
- Un método `to_string()` para la representación textual de cada nodo
- Un método `resolve_names()` para el análisis semántico

### Jerarquía de Clases

El AST se organiza en tres categorías principales de nodos:

1. **Expresiones** (`expression.hpp`)
2. **Declaraciones** (`declaration.hpp`)
3. **Sentencias** (`statement.hpp`)

## Tipos de Datos y Enumeraciones

### DurationType
```cpp
enum class DurationType {
    SEMICORCHEA,   // Semicorchea
    CORCHEA,       // Corchea
    NEGRA,         // Negra
    BLANCA         // Blanca
};
```

Define los tipos de duración posibles para las notas musicales.

### KeyMode
```cpp
enum class KeyMode {
    MAYOR,  // Mayor
    MENOR   // Menor
};
```

Define los modos posibles para las tonalidades musicales.

## Expresiones

Las expresiones musicales se definen en `expression.hpp` mediante la clase base abstracta `Expression`:

```cpp
class Expression : public ASTNodeInterface {
};
```

Se implementan las siguientes clases concretas:

### NoteExpression

```cpp
class NoteExpression : public Expression {
public:
    NoteExpression(const std::string& note_name, int octave) noexcept;
    std::string get_note_name() const noexcept;
    int get_octave() const noexcept;
    // Métodos heredados...
private:
    std::string note_name;
    int octave;
};
```

Representa una expresión que produce una nota musical.

### DurationExpression

```cpp
class DurationExpression : public Expression {
public:
    DurationExpression(DurationType type) noexcept;
    DurationType get_duration_type() const noexcept;
    // Métodos heredados...
private:
    DurationType duration_type;
};
```

Representa una expresión que produce una duración.

## Declaraciones

Las declaraciones musicales se definen en `declaration.hpp` mediante la clase base abstracta `Declaration`:

```cpp
class Declaration : public ASTNodeInterface {
};
```

Se implementan las siguientes clases concretas:

### TempoDeclaration

```cpp
class TempoDeclaration : public Declaration {
public:
    TempoDeclaration(int tempo_value) noexcept;
    int get_tempo_value() const noexcept;
    // Métodos heredados...
private:
    int tempo_value;
};
```

Representa una declaración de tempo.

### TimeSignatureDeclaration

```cpp
class TimeSignatureDeclaration : public Declaration {
public:
    TimeSignatureDeclaration(int numerator, int denominator) noexcept;
    int get_numerator() const noexcept;
    int get_denominator() const noexcept;
    // Métodos heredados...
private:
    int numerator;
    int denominator;
};
```

Representa una declaración de compás.

### KeyDeclaration

```cpp
class KeyDeclaration : public Declaration {
public:
    KeyDeclaration(const std::string& root_note, KeyMode mode) noexcept;
    std::string get_root_note() const noexcept;
    KeyMode get_mode() const noexcept;
    // Métodos heredados...
private:
    std::string root_note;
    KeyMode mode;
};
```

Representa una declaración de tonalidad.

## Sentencias

Las sentencias musicales se definen en `statement.hpp`:

```cpp
class Statement : public ASTNodeInterface {
};
```

Se implementan las siguientes clases concretas:

### NoteStatement

```cpp
class NoteStatement : public Statement {
public:
    NoteStatement(Expression* note, Expression* duration) noexcept;
    Expression* get_note() const noexcept;
    Expression* get_duration() const noexcept;
    // Métodos heredados...
private:
    Expression* note;
    Expression* duration;
};
```

Representa una nota musical con su duración.

## Programa Musical

La clase raíz del AST es `MusicProgram`:

```cpp
class MusicProgram : public ASTNodeInterface {
public:
    MusicProgram() noexcept;
    ~MusicProgram() noexcept;
    
    void add_declaration(Declaration* declaration) noexcept;
    void add_statement(Statement* statement) noexcept;
    
    const std::vector<Declaration*>& get_declarations() const noexcept;
    const std::vector<Statement*>& get_statements() const noexcept;
    
    // Métodos heredados...
private:
    std::vector<Declaration*> declarations;
    std::vector<Statement*> statements;
};
```

Representa un programa musical completo, conteniendo declaraciones y sentencias.

## Extensibilidad

El sistema del AST está diseñado para ser extensible:

1. Nuevas expresiones pueden añadirse implementando subclases de `Expression`
2. Nuevas declaraciones pueden añadirse implementando subclases de `Declaration`
3. Nuevas sentencias pueden añadirse implementando subclases de `Statement`

## Ejemplo de Creación de AST

```cpp
// Crear un programa musical
MusicProgram program;

// Declaraciones
program.add_declaration(new TempoDeclaration(60));
program.add_declaration(new TimeSignatureDeclaration(4, 4));
program.add_declaration(new KeyDeclaration("Do", KeyMode::MAYOR));

// Nota musical
program.add_statement(new NoteStatement(
    new NoteExpression("Do", 4),
    new DurationExpression(DurationType::NEGRA)
));
```

## Memoria y Destrucción

Cada nodo del AST es responsable de la destrucción recursiva de sus nodos hijos a través del método `destroy()`. Esto asegura que toda la memoria sea liberada correctamente cuando se destruye el nodo raíz.

## Análisis Semántico

El método `resolve_names()` en cada nodo permite realizar la validación semántica utilizando la tabla de símbolos. Este método retorna:
- `true` si el nodo y todos sus hijos son semánticamente válidos
- `false` si hay algún error semántico

Para más detalles sobre el análisis semántico, consulte el documento correspondiente. 
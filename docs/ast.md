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
};
```

Esta interfaz proporciona:
- Un destructor virtual para permitir la destrucción polimórfica
- Un método `destroy()` para la liberación manual de recursos
- Un método `to_string()` para la representación textual de cada nodo

### Jerarquía de Clases

El AST se organiza en tres categorías principales de nodos:

1. **Tipos de Datos** (`datatype.hpp`)
2. **Expresiones** (`expression.hpp`)
3. **Declaraciones** (`declaration.hpp`)
4. **Sentencias** (`statement.hpp`)

## Tipos de Datos

Los tipos de datos básicos son modelados en `datatype.hpp` mediante la clase base abstracta `Datatype`:

```cpp
enum class DataType {
    NOTE,          // Representa la nota musical (Do, Re, Mi, etc.)
    DURATION,      // Representa la duración de una nota
    TEMPO,         // Representa la velocidad de ejecución
    TIME_SIGNATURE,// Representa el compás (4/4, 3/4, etc.)
    KEY            // Representa la tonalidad musical
};

class Datatype : public ASTNodeInterface {
public:
    virtual DataType get_type() const noexcept = 0;
};
```

Se implementan las siguientes clases concretas:

### Note

```cpp
class Note : public Datatype {
public:
    Note(const std::string& note_name, int octave) noexcept;
    std::string get_note_name() const noexcept;
    int get_octave() const noexcept;
    // Métodos heredados...
private:
    std::string note_name;
    int octave;
};
```

Representa una nota musical con nombre (Do, Re, Mi, etc.) y octava.

### Duration

```cpp
enum class DurationType {
    SEMICORCHEA,   // Semicorchea
    CORCHEA,       // Corchea
    NEGRA,         // Negra
    BLANCA         // Blanca
};

class Duration : public Datatype {
public:
    Duration(DurationType type) noexcept;
    DurationType get_duration_type() const noexcept;
    // Métodos heredados...
private:
    DurationType duration_type;
};
```

Representa la duración de una nota musical.

### Tempo

```cpp
class Tempo : public Datatype {
public:
    Tempo(int bpm) noexcept;
    int get_bpm() const noexcept;
    // Métodos heredados...
private:
    int bpm;
};
```

Representa la velocidad de ejecución en beats por minuto (BPM).

### TimeSignature

```cpp
class TimeSignature : public Datatype {
public:
    TimeSignature(int numerator, int denominator) noexcept;
    int get_numerator() const noexcept;
    int get_denominator() const noexcept;
    // Métodos heredados...
private:
    int numerator;
    int denominator;
};
```

Representa el compás musical como una fracción (numerador/denominador).

### Key

```cpp
enum class KeyMode {
    MAJOR,  // Mayor
    MINOR   // Menor
};

class Key : public Datatype {
public:
    Key(const std::string& root_note, KeyMode mode) noexcept;
    std::string get_root_note() const noexcept;
    KeyMode get_mode() const noexcept;
    // Métodos heredados...
private:
    std::string root_note;
    KeyMode mode;
};
```

Representa la tonalidad musical con una nota raíz y un modo (mayor o menor).

## Expresiones

Las expresiones musicales se definen en `expression.hpp` mediante la clase base abstracta `Expression`:

```cpp
class Expression : public ASTNodeInterface {
public:
    virtual DataType get_expression_type() const noexcept = 0;
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
    Note* note;
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
    Duration* duration;
};
```

Representa una expresión que produce una duración.

## Declaraciones

Las declaraciones musicales se definen en `declaration.hpp` mediante la clase base abstracta `Declaration`:

```cpp
class Declaration : public ASTNodeInterface {
public:
    virtual DataType get_declaration_type() const noexcept = 0;
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
    Tempo* tempo;
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
    TimeSignature* time_signature;
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
    Key* key;
};
```

Representa una declaración de tonalidad.

## Sentencias

Las sentencias musicales se definen en `statement.hpp` mediante la clase base abstracta `Statement`:

```cpp
class Statement : public ASTNodeInterface {
    // Clase base para los statements
};
```

Se implementan las siguientes clases concretas:

### NoteStatement

```cpp
class NoteStatement : public Statement {
public:
    NoteStatement(NoteExpression* note, DurationExpression* duration) noexcept;
    NoteExpression* get_note() const noexcept;
    DurationExpression* get_duration() const noexcept;
    // Métodos heredados...
private:
    NoteExpression* note;
    DurationExpression* duration;
};
```

Representa una sentencia de nota musical, que combina una nota con una duración.

## Programa Musical

El AST también proporciona una estructura para representar un programa musical completo, implementada en `demo_c_function.cpp`:

```cpp
class Program : public ASTNodeInterface {
public:
    Program() noexcept = default;
    void add_declaration(Declaration* decl) noexcept;
    void add_statement(Statement* stmt) noexcept;
    // Métodos heredados...
private:
    std::forward_list<Declaration*> declarations;
    std::forward_list<Statement*> statements;
};
```

Esta clase actúa como contenedor de alto nivel para todas las declaraciones y sentencias en un programa musical.

## Gestión de Memoria

El AST implementa un sistema de gestión de memoria manual que sigue estas reglas:

1. Todos los nodos se crean dinámicamente con `new`
2. Cada nodo es responsable de liberar sus propios recursos en su método `destroy()`
3. Los nodos compuestos son responsables de llamar a `destroy()` en sus nodos hijos
4. Los destructores del AST llaman a `destroy()` para garantizar una liberación adecuada de recursos

## Ejemplo de Uso

El archivo `demo_c_function.cpp` proporciona un ejemplo completo de cómo construir y utilizar el AST:

```cpp
int main() {
    // Crear un programa musical
    Program program;
    
    // Agregar declaraciones
    program.add_declaration(new TempoDeclaration(60));
    program.add_declaration(new TimeSignatureDeclaration(7, 8));
    program.add_declaration(new KeyDeclaration("Si", KeyMode::MAJOR));
    
    // Agregar notas
    program.add_statement(new NoteStatement(
        new NoteExpression("Do#", 5),
        new DurationExpression(DurationType::CORCHEA)
    ));
    
    // Imprimir la representación del AST
    std::cout << program.to_string() << std::endl;
    
    // Liberar recursos
    program.destroy();
    
    return 0;
}
```

Este ejemplo crea un programa musical con tempo, compás y tonalidad, seguido de una nota musical, y luego imprime su representación.

## Compilación

El módulo AST incluye un Makefile para facilitar la compilación:

```bash
# Compilar todo el AST
make

# Ejecutar el programa de demostración
make test
```

Esto compila todos los componentes del AST y ejecuta el programa de demostración, que muestra la representación textual del AST construido.

## Extensibilidad

La arquitectura del AST está diseñada para ser extensible:

1. Nuevos tipos de datos pueden añadirse implementando nuevas subclases de `Datatype`
2. Nuevas expresiones pueden añadirse implementando nuevas subclases de `Expression`
3. Nuevas declaraciones pueden añadirse implementando nuevas subclases de `Declaration`
4. Nuevas sentencias pueden añadirse implementando nuevas subclases de `Statement`

Esto permite que el lenguaje musical se extienda con nuevas características sin alterar la estructura fundamental del AST. 
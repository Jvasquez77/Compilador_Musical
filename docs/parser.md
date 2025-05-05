# Documentación del Analizador Sintáctico para Lenguaje Musical

## Introducción

Este documento describe la implementación del analizador sintáctico (parser) y el modelo de expresiones para el compilador de lenguaje musical. El sistema permite procesar archivos de partituras musicales con la extensión `.mus` y convertirlos en una representación de objetos en memoria que posteriormente se pueden analizar o transformar.

## Estructura del Sistema

El sistema está compuesto por tres componentes principales:

1. **Scanner** (en `scanner.flex`): Escanea y tokeniza el contenido del archivo de música utilizando Flex.
2. **Parser** (en `parser.bison`): Define la gramática del lenguaje musical utilizando Bison.
3. **Modelo de Expresiones** (en `expression.hpp` y `expression.cpp`): Define las clases que representan los conceptos musicales.

## Modelo de Expresiones

El modelo de expresiones abstrae la lógica del parser en clases bien definidas que representan los elementos musicales. Todas las clases heredan de la clase base abstracta `Expression`.

### Clase Base

```cpp
class Expression {
public:
    virtual ~Expression();
    virtual void destroy() noexcept = 0;
    virtual std::string to_string() const noexcept = 0;
    
    virtual std::string getStringValue() const noexcept;
    virtual int getIntValue() const noexcept;
    virtual void addInstruction(Expression* instruction) noexcept;
};
```

La clase base `Expression` tiene:
- Destructor virtual para permitir la destrucción polimórfica.
- Método abstracto `destroy()` para gestionar la liberación manual de recursos.
- Método abstracto `to_string()` para convertir la expresión a una representación textual.
- Métodos virtuales adicionales que pueden ser sobrescritos por clases derivadas para obtener valores específicos.

### Clases de Tipos Básicos

#### Number

```cpp
class Number : public Expression {
public:
    Number(int val) noexcept;
    void destroy() noexcept override;
    std::string to_string() const noexcept override;
    int getIntValue() const noexcept override;
private:
    int value;
};
```

Representa un valor numérico entero, usado para tempo, numerador y denominador del compás.

#### StringExpression

```cpp
class StringExpression : public Expression {
public:
    StringExpression(const std::string& val) noexcept;
    void destroy() noexcept override;
    std::string to_string() const noexcept override;
    std::string getStringValue() const noexcept override;
private:
    std::string value;
};
```

Representa un valor de tipo cadena, utilizado para nombres de notas.

### Clases para Elementos Musicales

#### Tempo

```cpp
class Tempo : public Expression {
public:
    Tempo(Number* val) noexcept;
    void destroy() noexcept override;
    std::string to_string() const noexcept override;
    int getTempo() const noexcept;
private:
    Number* tempo_value;
};
```

Representa el tempo musical en beats por minuto (BPM).

#### TimeSignature (Compás)

```cpp
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
```

Representa la estructura rítmica del compás, como 4/4, 3/4, etc.

#### Key (Tonalidad)

```cpp
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
```

Representa la tonalidad musical, incluyendo la nota base (Do, Re, etc.) y el modo (Mayor o Menor).

#### Duration (Duración)

```cpp
enum class Duration {
    BLANCA,
    NEGRA,
    CORCHEA,
    SEMICORCHEA
};
```

Enumeración que define las duraciones posibles de una nota musical.

#### Note (Nota)

```cpp
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
```

Representa una nota musical individual con su nombre, octava y duración.

#### Program (Programa)

```cpp
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
```

Contenedor principal que representa un programa musical completo, almacenando una secuencia de instrucciones musicales (tempo, compás, tonalidad, notas).

## Componentes del Sistema

### Scanner (scanner.flex)

El scanner utiliza Flex para reconocer los tokens del lenguaje musical:

- **Palabras clave**: `Tonalidad`, `Tempo`, `Compas`
- **Duraciones de notas**: `Blanca`, `Negra`, `Corchea`, `Semicorchea`
- **Modos tonales**: `M` (Mayor), `m` (Menor)
- **Notas musicales**: Tanto en notación latina (`Do`, `Re`, etc.) como en notación inglesa (`C`, `D`, etc.)
- **Alteraciones**: `#` (sostenido), `b` (bemol)
- **Notas con octava**: Combinaciones de nota, alteración opcional y número de octava (ej: `Do4`, `Fa#3`)
- **Números y otros símbolos**: Enteros, barras de división, comentarios (comenzando con `//`)

### Parser (parser.bison)

El parser utiliza Bison para definir la gramática del lenguaje musical:

- **Programa**: Secuencia de instrucciones musicales
- **Instrucciones**: Tempo, compás, tonalidad y notas
- **Tempo**: Palabra clave `Tempo` seguida de un número
- **Compás**: Palabra clave `Compas` seguida de dos números separados por una barra (`/`)
- **Tonalidad**: Palabra clave `Tonalidad` seguida de una nota base (posiblemente alterada) y un modo (Mayor o Menor)
- **Nota**: Nota con octava seguida de una duración

El parser también incluye funciones auxiliares para extraer la octava y el nombre de la nota de los tokens reconocidos.

### Programa Principal (main.cpp)

El programa principal:

1. Verifica que se proporcione un archivo con extensión `.mus` como argumento
2. Abre el archivo y lo prepara para el análisis
3. Inicia el parser para analizar el contenido
4. Si el análisis tiene éxito, muestra la representación textual del programa musical
5. Gestiona la limpieza de recursos y el manejo de errores

## Gestión de Memoria

El sistema implementa un esquema de gestión de memoria manual mediante los métodos `destroy()`:

- Cada clase es responsable de liberar sus propios recursos en su método `destroy()`
- La clase `Program` se encarga de liberar todas las instrucciones que contiene
- El destructor de `Program` llama a `destroy()` para garantizar la liberación adecuada de recursos
- Las instancias de expresiones se crean dinámicamente con `new` y se liberan mediante `delete` en sus respectivos métodos `destroy()`

## Ejemplo de Código Válido

```
Tempo 120
Compas 4/4
Tonalidad Do M

// Melodía simple
Do4 Negra
Re4 Negra
Mi4 Negra
Fa4 Negra
Sol4 Blanca
La4 Corchea
Si4 Corchea
Do5 Blanca
```

## Compilación y Ejecución

El proyecto incluye un Makefile para facilitar la compilación:

```bash
# Compilar el proyecto
make

# Ejecutar el parser con un archivo de entrada
./parser ejemplo.mus
```

Al ejecutarse correctamente, el programa mostrará la representación textual del programa musical analizado.

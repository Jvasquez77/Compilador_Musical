# Documentación del Analizador Sintáctico para Lenguaje Musical

## Introducción

Este documento describe la implementación del analizador sintáctico (parser) y el modelo de expresiones para un compilador de lenguaje musical. El sistema permite procesar archivos de partituras musicales con la extensión `.mus` y convertirlos en una representación de objetos en memoria.

## Estructura del Sistema

El sistema está compuesto por tres componentes principales:

1 **Scanner** (en `scanner.flex`): escanea y tokeniza el contenido del lenguaje musical.
2. **Parser** (en `parser.bison`): Define la gramática del lenguaje musical utilizando Bison.
3. **Modelo de Expresiones** (en `expression.hpp` y `expression.cpp`): Define las clases que representan los conceptos musicales.

## Modelo de Expresiones

El modelo de expresiones abstrae la lógica del parser en clases bien definidas que representan los elementos musicales. Todas las clases heredan de una clase base común `Expression`.

### Clase Base

La clase base `Expression` proporciona una interfaz común para todas las expresiones musicales:

- `destroy()`: Método para gestionar la liberación de recursos.
- `eval()`: Método para evaluar la expresión y devolver un valor numérico.
- `to_string()`: Método para convertir la expresión a una representación textual.

### Clases Principales

#### Configuration

Representa la configuración musical que aparece al inicio de un archivo `.mus`:

- **Tempo**: Velocidad de la pieza en beats por minuto (BPM).
- **Compás**: Estructura rítmica de la pieza (por ejemplo, 4/4, 3/4, 7/8).
- **Tonalidad**: Nota central y modo (mayor o menor).

Métodos principales:
- `setTempo()`, `hasTempo()`: Establecer y verificar el tempo.
- `setTimeSignature()`, `hasTimeSignature()`: Establecer y verificar el compás.
- `setKey()`, `hasKey()`: Establecer y verificar la tonalidad.
- `isComplete()`: Verifica si la configuración tiene todos los elementos necesarios.

#### Note

Representa una nota musical individual con sus propiedades:

- Nombre de la nota (Do, Re, Mi, etc.)
- Alteración (sostenido #, bemol b, o ninguna)
- Octava (número entero)
- Duración (negra, blanca, corchea, etc.)

Proporciona métodos para acceder a estas propiedades y para calcular su valor MIDI equivalente mediante `eval()`.

#### MusicProgram

Es el contenedor principal que representa un programa musical completo:

- Contiene una instancia de `Configuration`.
- Almacena una colección de instancias de `Note`.
- Gestiona la liberación de memoria de todos sus componentes.

## Relación con el Parser

El parser utiliza estas clases para construir una representación en memoria del programa musical:

1. Crea una instancia de `Configuration` al inicio del análisis.
2. Establece los valores de tempo, compás y tonalidad según se encuentran en el código fuente.
3. A medida que analiza las notas, crea instancias de `Note` con los valores correspondientes.
4. Finalmente, crea una instancia de `MusicProgram` que contiene la configuración y todas las notas.

## Gestión de Memoria

El sistema implementa un esquema de gestión de memoria manual mediante los métodos `destroy()`:

- Las clases sin recursos complejos (`Configuration`, `Note`) tienen implementaciones simples de `destroy()`.
- `MusicProgram` implementa `destroy()` para liberar tanto su configuración como todas sus notas.
- El destructor de `MusicProgram` llama a `destroy()` para garantizar la liberación de recursos.

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

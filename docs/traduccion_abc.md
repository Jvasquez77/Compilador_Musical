# Proceso de Traducción a Formato ABC

## Introducción

El formato ABC es una notación textual para representar música, especialmente útil para transcribir melodías tradicionales y generar partituras. En nuestro compilador musical, la fase de traducción convierte el AST (Árbol de Sintaxis Abstracta) resultante del análisis semántico en una representación ABC válida que entra en el entorno de protocolos de comunicacion como MIDI.

## Componentes de la Traducción ABC

### Cabecera ABC

Cada archivo ABC comienza con una cabecera que define diversos parámetros de la partitura:

| Campo | Descripción             | Implementación                                                         |
|-------|-------------------------|------------------------------------------------------------------------|
| X:1   | Número de referencia    | Se asigna "1" como referencia predeterminada                           |
| T:    | Título de la pieza      | Se utiliza "LJ CERTIFIED TRANSLATION" como título predeterminado       |
| Q:    | Tempo (velocidad)       | Derivado de la declaración `TempoDeclaration` (Q:1/4=60)               |
| M:    | Compás                  | Derivado de la declaración `TimeSignatureDeclaration` (ejemplo: M:7/8) |
| L:    | Longitud predeterminada | Se establece en 1/8 (corchea) como unidad básica                       |
| K:    | Tonalidad y modo        | Derivado de la declaración `KeyDeclaration` (ejemplo: K:Bmaj)          |

### Traducción de Notas Musicales

#### Notas Básicas

Las notas musicales se representan según la siguiente notación:

| Nota en español | Nota en ABC |
|-----------------|-------------|
| Do              | C           |
| Re              | D           |
| Mi              | E           |
| Fa              | F           |
| Sol             | G           |
| La              | A           |
| Si              | B           |

#### Octavas

La octava se representa mediante comillas o comas:

| Octava | Representación en ABC|
|--------|----------------------|
| 1      | C,,,                 |
| 2      | C,,                  |
| 3      | C,                   |
| 4      | C (octava central)   |
| 5      | c                    |
| 6      | c'                   |
| 7      | c''                  |

La implementación maneja esto calculando el desplazamiento relativo a la octava 4 (central):
- Por cada octava por encima de 4, se añade una comilla simple (')
- Por cada octava por debajo de 4, se añade una coma (,)

#### Alteraciones (Sostenidos y Bemoles)

| Alteración    | Representación en ABC |
|---------------|-----------------------|
| Sostenido (#) | ^C                    |
| Bemol (b)     | _C                    |


#### Duración de Notas

La duración se representa como un sufijo numérico relativo a la unidad base (L:1/8):

| Figura      | Duración relativa | ABC |
|-------------|-------------------|-----|
| Blanca      | 4                 | C4  |
| Negra       | 2                 | C2  |
| Corchea     | 1                 | C   |
| Semicorchea | 1/2               | C/2 |

## Proceso de Traducción

### 1. Inicio de la Traducción

```cpp
// Cabecera mínima ABC
out << "X:1\n";
out << "T:LJ CERTIFIED TRANSLATION\n";
```

### 2. Traducción de Declaraciones

Las declaraciones del programa musical se procesan primero, estableciendo los parámetros básicos:

```cpp
// Procesar todas las declaraciones primero
for (const auto& decl : declarations) {
    decl->to_abc(out, beatCounter);
}
```

### 3. Traducción de Notas (Statements)

Cada nota musical se traduce según los siguientes pasos:

1. **Conversión de nombre de nota**: De notación latina (Do, Re, Mi...) a anglosajona (C, D, E...)
2. **Aplicación de alteraciones**: Sostenidos (^) o bemoles (_)
3. **Ajuste de octava**: Aplicación de comillas o comas según la octava
4. **Asignación de duración**: Sufijo numérico basado en la figura musical

Ejemplo de implementación:
```cpp
std::string NoteExpression::to_abc() const noexcept {
    std::string abc_note;
    
    // Convertir nombre de nota
    // (Do->C, Re->D, etc.)
    
    // Aplicar alteraciones si corresponde
    // (#->^, b->_)
    
    // Ajustar octava
    // (comillas o comas)
    
    // Asignar duración
    // (según figura musical)
    
    return abc_note;
}
```

### 4. Control de Compases

El compilador mantiene un contador de tiempos (beatCounter) para insertar barras de compás cuando se completa un compás:

```cpp
// Insertar barra de compás cuando se completa un compás
if (std::fmod(beatCounter, 7.0) == 0.0) {
    out << "| ";
}
```

### 5. Finalización

Al terminar de procesar todas las notas, se cierra la partitura con una barra final:

```cpp
// Finalizar la partitura con una barra final
out << "|\n";
```

## Ejemplo Completo

Una composición simple en nuestro lenguaje:

```
Tempo 60
Compas 4/4
Tonalidad Do M

Do4 Negra
Re4 Negra
Mi4 Negra
Fa4 Negra
```

Se traduce a ABC como:

```
X:1
T:LJ CERTIFIED TRANSLATION
Q:1/4=60
M:4/4
L:1/8
K:Cmaj
C2 D2 E2 F2 |
```
 El formato ABC generado es compatible con herramientas estándar de procesamiento ABC y admisible en el protocolo de comunicacion de MIDI.

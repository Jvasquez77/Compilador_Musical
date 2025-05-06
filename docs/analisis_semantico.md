# Análisis Semántico en el Compilador Musical

## Resumen

El análisis semántico es una fase crítica en nuestro compilador musical que verifica la validez semántica del código, asegurando que las referencias a símbolos sean válidas y que las declaraciones cumplan con las reglas del lenguaje musical.

Este documento describe la implementación del sistema de análisis semántico, incluyendo:
- La tabla de símbolos utilizada para el seguimiento de declaraciones
- El método `resolve_names()` agregado a todos los nodos del AST
- Las reglas semánticas específicas para las declaraciones musicales
- Un programa de demostración que ilustra el análisis semántico en acción

## Estructura del Análisis Semántico

### 1. Tabla de Símbolos

Implementamos una tabla de símbolos para realizar el seguimiento de los símbolos declarados en el programa musical. Esta tabla está definida en:
- `/Semantic_Analysis/symbol_table.hpp`
- `/Semantic_Analysis/symbol_table.cpp`

La tabla de símbolos ofrece las siguientes funcionalidades:
- Soporte para ámbitos anidados (`enter_scope()` y `exit_scope()`)
- Inserción de símbolos (`insert(name)`)
- Búsqueda de símbolos a través de ámbitos (`lookup(name)`)
- Verificación de existencia de símbolos (`contains(name)`)

Cada símbolo en la tabla contiene:
- Un nombre (como string)

### 2. Modificación del AST para el Análisis Semántico

#### Método `resolve_names()`

La interfaz de todos los nodos AST (`ASTNodeInterface`) incluye un método virtual puro:

```cpp
virtual bool resolve_names(SymbolTable& table) noexcept = 0;
```

Este método es implementado en cada clase derivada para:
1. Verificar la validez semántica del nodo
2. Registrar los símbolos declarados en la tabla de símbolos
3. Verificar que las referencias a símbolos sean válidas
4. Retornar `true` si no hay errores semánticos, `false` de lo contrario

#### Implementaciones Específicas

##### Declaraciones

- **TempoDeclaration**: Verifica que el tempo sea positivo y que no se haya declarado previamente.
- **TimeSignatureDeclaration**: Verifica que el numerador sea positivo, el denominador sea válido (2, 4, 8 o 16) y que no se haya declarado previamente.
- **KeyDeclaration**: Verifica que la nota raíz sea válida y que no se haya declarado previamente.

##### Expresiones

- **NoteExpression**: Verifica que la nota sea válida y que esté dentro del rango permitido.
- **DurationExpression**: Verifica que la duración sea válida.

##### Statements

- **NoteStatement**: Verifica que la nota y la duración sean válidas.

##### Nodo Raíz

- **MusicProgram**: Coordina el análisis semántico de todo el programa, llamando a `resolve_names()` en todos los nodos hijos y verificando que existan las declaraciones obligatorias.

## Reglas Semánticas Implementadas

1. **Declaraciones únicas**:
   - Tempo, compás y tonalidad solo pueden declararse una vez en el programa.

2. **Validez de los valores**:
   - Tempo: Debe estar en el rango de Larghissimo a Prestissimo (20-200 BPM).
   - Compás (Time Signature): 
     - Numerador debe ser mayor a 1 y menor a 12.
     - Denominador debe ser 2, 4, 8 o 16.
   - Tonalidad (Key): 
     - La nota raíz debe ser válida (Do, Re, Mi, etc., con alteraciones válidas).

3. **Validez de notas**:
   - Las notas deben estar en el conjunto de notas musicales válidas.
   - La octava debe estar en el rango 1-8.

## Programa de Demostración

Se creó un programa de demostración en `/Semantic_Analysis/demo_program.cpp` que ilustra el proceso de análisis semántico. Este programa:

1. Crea manualmente un AST que representa un programa musical con:
   - Declaración de tempo (60)
   - Declaración de compás (7/8)
   - Declaración de tonalidad (Si Mayor)
   - Múltiples statements de notas con diferentes valores y duraciones

2. Realiza el análisis semántico sobre este AST:
   - Crea una tabla de símbolos
   - Llama a `resolve_names()` en el nodo raíz
   - Reporta si hay errores semánticos

3. Muestra el AST generado

## Ejemplo de Uso

```cpp
// Crear un programa musical
MusicProgram* program = new MusicProgram();

// Agregar declaraciones
program->add_declaration(new TempoDeclaration(60));
program->add_declaration(new TimeSignatureDeclaration(7, 8));
program->add_declaration(new KeyDeclaration("Si", KeyMode::MAYOR));

// Agregar statements (notas)
program->add_statement(new NoteStatement(
    new NoteExpression("Sol", 4),
    new DurationExpression(DurationType::CORCHEA)
));

// Realizar análisis semántico
SymbolTable symbol_table;
bool semantic_result = program->resolve_names(symbol_table);

if (semantic_result) {
    std::cout << "Análisis semántico completado con éxito." << std::endl;
} else {
    std::cout << "Se encontraron errores en el análisis semántico." << std::endl;
}
```

## Compilación y Ejecución

Se ha creado un Makefile en `/Semantic_Analysis/Makefile` que compila el programa de demostración y todas sus dependencias. Para compilar y ejecutar:

```
cd Semantic_Analysis
make all
./demo_program
```

## Conclusión

La implementación del análisis semántico representa un paso fundamental en nuestro compilador musical, permitiendo validar la corrección semántica de los programas antes de proceder a etapas posteriores como la generación de código. 

La arquitectura modular basada en el patrón Visitor (con el método `resolve_names()`) facilita la extensión del sistema para agregar más reglas semánticas en el futuro según sea necesario. 
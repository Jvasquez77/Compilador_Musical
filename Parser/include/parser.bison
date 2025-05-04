%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "expression.hpp"

extern int yylex();
extern char* yytext;
int yyerror(const char* s);

#define YYSTYPE Expression*
#define YYDEBUG 1

// Resultado del parser
int parser_result = 0;  // 0 = éxito, otro valor = error
MusicProgram* program_result = nullptr;

// Variables temporales para parsing
Configuration* current_config = nullptr;
std::string temp_note;
std::string temp_alteration;
int temp_octave = 0;
std::string temp_duration;
int temp_num = 0;  // Variable temporal para almacenar el numerador

// Función para extraer la nota y octava de TOKEN_NOTA_COMPLETA
void extract_note_octave(char* text) {
    int len = strlen(text);
    if (len < 2) return;
    
    // Último caracter es la octava
    char octave_char = text[len-1];
    temp_octave = octave_char - '0';
    
    // Extraer el nombre de la nota
    text[len-1] = '\0';  // Eliminar el número
    temp_note = text;
    temp_alteration = "";
}
%}

%token TOKEN_TONALIDAD TOKEN_TEMPO TOKEN_COMPAS
%token TOKEN_BLANCA TOKEN_NEGRA TOKEN_CORCHEA TOKEN_SEMICORCHEA
%token TOKEN_NOTA_DO TOKEN_NOTA_RE TOKEN_NOTA_MI TOKEN_NOTA_FA
%token TOKEN_NOTA_SOL TOKEN_NOTA_LA TOKEN_NOTA_SI
%token TOKEN_SOSTENIDO TOKEN_BEMOL
%token TOKEN_MAYOR TOKEN_MENOR
%token TOKEN_NUMERO TOKEN_BARRA
%token TOKEN_NOTA_COMPLETA
%token TOKEN_IDENTIFIER
%token TOKEN_COMENTARIO

// Definir precedencia para resolver conflictos
%left TOKEN_SOSTENIDO TOKEN_BEMOL

%%
programa
    : configuracion secuencia_notas  { 
        if (!current_config || !current_config->isComplete()) {
            yyerror("Configuración incompleta. Se requiere Tempo, Compas y Tonalidad.");
            YYERROR;
        } else {
            program_result = new MusicProgram(current_config);
            parser_result = 0;
            $$ = program_result;
        }
    }
    ;

configuracion
    : /* vacío */ { 
        current_config = new Configuration(); 
        $$ = current_config;
    }
    | configuracion config_item { 
        $$ = current_config; 
    }
    ;

config_item
    : config_tempo { 
        $$ = current_config; 
    }
    | config_compas { 
        $$ = current_config; 
    }
    | config_tonalidad { 
        $$ = current_config; 
    }
    | TOKEN_COMENTARIO { 
        $$ = current_config; 
    }
    ;

config_tempo
    : TOKEN_TEMPO TOKEN_NUMERO {
        int tempo_val = atoi(yytext);
        
        if (tempo_val <= 0) {
            yyerror("El tempo debe ser un valor positivo");
            YYERROR;
        }
        if (current_config->hasTempo()) {
            yyerror("El tempo ya ha sido definido");
            YYERROR;
        } else {
            current_config->setTempo(tempo_val);
            $$ = current_config;
        }
    }
    ;

config_compas
    : TOKEN_COMPAS TOKEN_NUMERO {
        temp_num = atoi(yytext);
        
        if (temp_num <= 0) {
            yyerror("El numerador del compás debe ser positivo");
            YYERROR;
        }
    } TOKEN_BARRA TOKEN_NUMERO {
        int den = atoi(yytext);
        
        if (den <= 0) {
            yyerror("El denominador del compás debe ser positivo");
            YYERROR;
        }
        if (current_config->hasTimeSignature()) {
            yyerror("El compás ya ha sido definido");
            YYERROR;
        } else {
            current_config->setTimeSignature(temp_num, den);
            $$ = current_config;
        }
    }
    ;

config_tonalidad
    : TOKEN_TONALIDAD nota_tonalidad modo {
        if (current_config->hasKey()) {
            yyerror("La tonalidad ya ha sido definida");
            YYERROR;
        } else {
            current_config->setKey(temp_note, temp_alteration);
            $$ = current_config;
        }
    }
    ;

nota_tonalidad
    : TOKEN_NOTA_DO { 
        temp_note = "Do"; 
    }
    | TOKEN_NOTA_RE { 
        temp_note = "Re"; 
    }
    | TOKEN_NOTA_MI { 
        temp_note = "Mi"; 
    }
    | TOKEN_NOTA_FA { 
        temp_note = "Fa"; 
    }
    | TOKEN_NOTA_SOL { 
        temp_note = "Sol"; 
    }
    | TOKEN_NOTA_LA { 
        temp_note = "La"; 
    }
    | TOKEN_NOTA_SI { 
        temp_note = "Si"; 
    }
    ;

modo
    : TOKEN_MAYOR { 
        temp_alteration = "M"; 
    }
    | TOKEN_MENOR { 
        temp_alteration = "m"; 
    }
    ;

secuencia_notas
    : /* vacío */ { 
        $$ = nullptr; 
    }
    | secuencia_notas nota_item { 
        $$ = $2; 
    }
    ;

nota_item
    : nota { 
        $$ = $1; 
    }
    | TOKEN_COMENTARIO { 
        $$ = nullptr; 
    }
    ;

nota
    : TOKEN_NOTA_COMPLETA duracion {
        extract_note_octave(yytext);
        $$ = new Note(temp_note, temp_alteration, temp_octave, temp_duration);
    }
    | nota_individual duracion {
        $$ = new Note(temp_note, temp_alteration, temp_octave, temp_duration);
    }
    ;

nota_individual
    : nota_basica octava {
        temp_alteration = "";
    }
    | nota_basica alteracion octava {
        /* temp_alteration ya fue establecido en la regla alteracion */
    }
    ;

nota_basica
    : TOKEN_NOTA_DO { 
        temp_note = "Do"; 
    }
    | TOKEN_NOTA_RE { 
        temp_note = "Re"; 
    }
    | TOKEN_NOTA_MI { 
        temp_note = "Mi"; 
    }
    | TOKEN_NOTA_FA { 
        temp_note = "Fa"; 
    }
    | TOKEN_NOTA_SOL { 
        temp_note = "Sol"; 
    }
    | TOKEN_NOTA_LA { 
        temp_note = "La"; 
    }
    | TOKEN_NOTA_SI { 
        temp_note = "Si"; 
    }
    ;

alteracion
    : TOKEN_SOSTENIDO { 
        temp_alteration = "#"; 
    }
    | TOKEN_BEMOL { 
        temp_alteration = "b"; 
    }
    ;

octava
    : TOKEN_NUMERO { 
        temp_octave = atoi(yytext); 
    }
    ;

duracion
    : TOKEN_BLANCA { 
        temp_duration = "blanca"; 
    }
    | TOKEN_NEGRA { 
        temp_duration = "negra"; 
    }
    | TOKEN_CORCHEA { 
        temp_duration = "corchea"; 
    }
    | TOKEN_SEMICORCHEA { 
        temp_duration = "semicorchea"; 
    }
    ;

%%

int yyerror(const char* s) {
    printf("Error de parseo: %s\n", s);
    return 1;
} 
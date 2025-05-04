%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cctype>
#include "expression.hpp"

// Definir YYSTYPE como Expression* para evitar problemas de inclusión
#define YYSTYPE Expression*

extern int yylex();
extern int yylineno;
extern char* yytext;
int yyerror(const char* msg);

// Función auxiliar para extraer la octava de una nota completa
int extraer_octava(const char* nota_completa) {
    int len = strlen(nota_completa);
    // La octava siempre es el último carácter
    if (len > 0) {
        char ultimo = nota_completa[len-1];
        if (isdigit(ultimo)) {
            return ultimo - '0';
        }
    }
    // Si no se encuentra una octava válida, devolver un valor por defecto
    return 4; // Octava 4 por defecto
}

// Función auxiliar para extraer solo el nombre de la nota sin la octava
std::string extraer_nombre_nota(const char* nota_completa) {
    int len = strlen(nota_completa);
    
    // Buscar dónde termina el nombre de la nota y comienza la octava
    // La octava siempre es el último carácter, si es un dígito
    if (len > 0 && isdigit(nota_completa[len-1])) {
        return std::string(nota_completa, len-1);
    }
    
    // Si no hay octava, devolver todo el string
    return std::string(nota_completa);
}

// Resultado del parser
Expression* parser_result{nullptr};
%}

// Declaración de tokens
%token TOKEN_TONALIDAD TOKEN_TEMPO TOKEN_COMPAS
%token TOKEN_BLANCA TOKEN_NEGRA TOKEN_CORCHEA TOKEN_SEMICORCHEA
%token TOKEN_MAYOR TOKEN_MENOR
%token TOKEN_BARRA
%token TOKEN_NUMERO
%token TOKEN_NOTA_DO TOKEN_NOTA_RE TOKEN_NOTA_MI TOKEN_NOTA_FA TOKEN_NOTA_SOL TOKEN_NOTA_LA TOKEN_NOTA_SI
%token TOKEN_SOSTENIDO TOKEN_BEMOL
%token TOKEN_NOTA_COMPLETA
%token TOKEN_COMENTARIO
%token TOKEN_IDENTIFIER

// Definición de la gramática
%%

programa : instruccion                  { 
                                          parser_result = new Program();
                                          parser_result->addInstruction($1);
                                          $$ = parser_result;
                                        }
         | programa instruccion         { 
                                          $1->addInstruction($2);
                                          $$ = $1;
                                        }
         ;

instruccion : tempo                     { $$ = $1; }
            | compas                    { $$ = $1; }
            | tonalidad                 { $$ = $1; }
            | nota                      { $$ = $1; }
            ;

tempo : TOKEN_TEMPO numero              { 
                                          $$ = new Tempo(new Number($2->getIntValue()));
                                          delete $2;
                                        }
      ;

compas : TOKEN_COMPAS numero TOKEN_BARRA numero  { 
                                                  $$ = new TimeSignature(
                                                    new Number($2->getIntValue()), 
                                                    new Number($4->getIntValue())
                                                  );
                                                  delete $2;
                                                  delete $4;
                                                }
       ;

tonalidad : TOKEN_TONALIDAD nota_base TOKEN_MAYOR  { 
                                                   $$ = new Key($2->getStringValue(), Key::KeyType::MAJOR);
                                                   delete $2;
                                                 }
          | TOKEN_TONALIDAD nota_alterada TOKEN_MAYOR {
                                                   $$ = new Key($2->getStringValue(), Key::KeyType::MAJOR);
                                                   delete $2;
                                                 }
          | TOKEN_TONALIDAD nota_base TOKEN_MENOR  { 
                                                   $$ = new Key($2->getStringValue(), Key::KeyType::MINOR);
                                                   delete $2;
                                                 }
          | TOKEN_TONALIDAD nota_alterada TOKEN_MENOR {
                                                   $$ = new Key($2->getStringValue(), Key::KeyType::MINOR);
                                                   delete $2;
                                                 }
          ;

nota_base : TOKEN_NOTA_DO               { $$ = new StringExpression("Do"); }
          | TOKEN_NOTA_RE               { $$ = new StringExpression("Re"); }
          | TOKEN_NOTA_MI               { $$ = new StringExpression("Mi"); }
          | TOKEN_NOTA_FA               { $$ = new StringExpression("Fa"); }
          | TOKEN_NOTA_SOL              { $$ = new StringExpression("Sol"); }
          | TOKEN_NOTA_LA               { $$ = new StringExpression("La"); }
          | TOKEN_NOTA_SI               { $$ = new StringExpression("Si"); }
          ;

nota_alterada : nota_base TOKEN_SOSTENIDO  { 
                                           $$ = new StringExpression($1->getStringValue() + "#");
                                           delete $1;
                                         }
              | nota_base TOKEN_BEMOL    { 
                                           $$ = new StringExpression($1->getStringValue() + "b");
                                           delete $1;
                                         }
              ;

nota : nota_con_octava TOKEN_BLANCA      { 
                                           $$ = new Note($1->getStringValue(), extraer_octava(yytext), Duration::BLANCA);
                                           delete $1;
                                         }
     | nota_con_octava TOKEN_NEGRA       { 
                                           $$ = new Note($1->getStringValue(), extraer_octava(yytext), Duration::NEGRA);
                                           delete $1;
                                         }
     | nota_con_octava TOKEN_CORCHEA     { 
                                           $$ = new Note($1->getStringValue(), extraer_octava(yytext), Duration::CORCHEA);
                                           delete $1;
                                         }
     | nota_con_octava TOKEN_SEMICORCHEA { 
                                           $$ = new Note($1->getStringValue(), extraer_octava(yytext), Duration::SEMICORCHEA);
                                           delete $1;
                                         }
     ;

nota_con_octava : TOKEN_NOTA_COMPLETA   { 
                                          $$ = new StringExpression(extraer_nombre_nota(yytext));
                                        }
                ;

numero : TOKEN_NUMERO                   { $$ = new Number(atoi(yytext)); }
       ;

%%

int yyerror(const char* msg) {
    fprintf(stderr, "Error de análisis (línea %d): %s\n", yylineno, msg);
    return 1;
}

// Función principal para análisis
Expression* parse() {
    yyparse();
    return parser_result;
} 
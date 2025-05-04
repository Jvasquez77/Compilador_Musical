#include <stdio.h>
#include <stdlib.h>
#include "token.h"

extern int yylex();
extern int yylineno;
extern char* yytext;
extern FILE* yyin;

int yyerror(const char* msg) {
    fprintf(stderr, "Error en línea %d: %s\n", yylineno, msg);
    return 1;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s archivo.mus\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (!file) {
        fprintf(stderr, "No se pudo abrir el archivo: %s\n", argv[1]);
        return 1;
    }
    
    yyin = file;
    
    printf("Analizando archivo: %s\n\n", argv[1]);
    printf("TOKEN\t\t\tTEXTO\n");
    printf("----------------------------------------\n");
    
    int token;
    while ((token = yylex()) != TOKEN_EOF) {
        printf("%-20s\t%s\n", token_str((token_t)token), yytext);
    }
    
    fclose(file);
    printf("\nAnálisis léxico completado.\n");
    
    return 0;
} 
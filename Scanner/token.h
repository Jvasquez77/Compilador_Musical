#pragma once

typedef enum
{
  TOKEN_EOF = 0,
  TOKEN_COMENTARIO = 258,
  TOKEN_TONALIDAD = 259,
  TOKEN_TEMPO = 260,
  TOKEN_COMPAS = 261,
  TOKEN_BLANCA = 262,
  TOKEN_NEGRA = 263,
  TOKEN_CORCHEA = 264,
  TOKEN_SEMICORCHEA = 265,
  TOKEN_MAYOR = 266,
  TOKEN_MENOR = 267,
  TOKEN_NUMERO = 268,
  TOKEN_BARRA = 269,
  TOKEN_NOTA_DO = 270,
  TOKEN_NOTA_RE = 271,
  TOKEN_NOTA_MI = 272,
  TOKEN_NOTA_FA = 273,
  TOKEN_NOTA_SOL = 274,
  TOKEN_NOTA_LA = 275,
  TOKEN_NOTA_SI = 276,
  TOKEN_SOSTENIDO = 277,
  TOKEN_BEMOL = 278,
  TOKEN_NOTA_COMPLETA = 279,
  TOKEN_IDENTIFIER = 280
}
token_t;

static inline const char* token_str(token_t t)
{
  switch(t)
  {
    case TOKEN_EOF: return "<EOF>";
    case TOKEN_COMENTARIO: return "<COMENTARIO>";
    case TOKEN_TONALIDAD: return "<TONALIDAD>";
    case TOKEN_TEMPO: return "<TEMPO>";
    case TOKEN_COMPAS: return "<COMPAS>";
    case TOKEN_BLANCA: return "<BLANCA>";
    case TOKEN_NEGRA: return "<NEGRA>";
    case TOKEN_CORCHEA: return "<CORCHEA>";
    case TOKEN_SEMICORCHEA: return "<SEMICORCHEA>";
    case TOKEN_MAYOR: return "<MAYOR>";
    case TOKEN_MENOR: return "<MENOR>";
    case TOKEN_NUMERO: return "<NUMERO>";
    case TOKEN_BARRA: return "<BARRA>";
    case TOKEN_NOTA_DO: return "<NOTA_DO>";
    case TOKEN_NOTA_RE: return "<NOTA_RE>";
    case TOKEN_NOTA_MI: return "<NOTA_MI>";
    case TOKEN_NOTA_FA: return "<NOTA_FA>";
    case TOKEN_NOTA_SOL: return "<NOTA_SOL>";
    case TOKEN_NOTA_LA: return "<NOTA_LA>";
    case TOKEN_NOTA_SI: return "<NOTA_SI>";
    case TOKEN_SOSTENIDO: return "<SOSTENIDO>";
    case TOKEN_BEMOL: return "<BEMOL>";
    case TOKEN_NOTA_COMPLETA: return "<NOTA_COMPLETA>";
    case TOKEN_IDENTIFIER: return "<IDENTIFICADOR>";
    default: return "<DESCONOCIDO>";
  }
} 
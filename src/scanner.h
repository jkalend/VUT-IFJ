//
// Created by Kalenda, Jan on 02.10.2022.
//

#ifndef IFJ_SCANNER_H
#define IFJ_SCANNER_H

#include "error.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

FILE *stream;

typedef enum {
    KW_ELSE,
    KW_FLOAT,
    KW_FUNCTION,
    KW_IF,
    KW_INT,
    KW_NULL,
    KW_RETURN,
    KW_STRING,
    KW_VOID,
    KW_WHILE,
    //KW_FOR,
    //KW_GLOBAL,
    //KW_BOOLEAN,
}Keyword;

typedef union {
    Keyword keyword;
    char *identifier;
    char *string;
    double number_float;
    long long number_int;
}Value;

typedef enum {
    T_VALID,
    T_KEYWORD,
    T_IDENTIFIER,
    T_STRING,
    T_INT,
    T_FLOAT,
    T_VAR,
    T_TYPE,
    T_PLUS,
    T_MINUS,
    T_MULTIPLY,
    T_DIVIDE,
    T_LESS,
    T_LESS_EQUAL,
    T_GREATER,
    T_GREATER_EQUAL,
    T_EQUAL,
    T_NOT_EQUAL,
    T_CONCATENATE,
    T_ASSIGN,
    T_SEMICOLON,
    T_COMMA,
    T_DOUBLE_DOT,
    T_LEFT_BRACKET,
    T_RIGHT_BRACKET,
    T_LEFT_BRACE,
    T_RIGHT_BRACE,
    T_AND,
    T_OR,
    T_EOF,
    T_ERROR,
}Type;

typedef struct {
    Value value;
    Type type;
    int line;
    int column[2];
}Token;

int get_token(Token *token);
long long convert_str_to_int(char*);
double convert_str_to_float(char*);
int kw_check(char*);
int free_memory(char*, int);

#endif //IFJ_SCANNER_H

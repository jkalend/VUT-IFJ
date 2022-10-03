//
// Created by Kalenda, Jan on 02.10.2022.
//

#ifndef IFJ_SCANNER_H
#define IFJ_SCANNER_H

#include "error.h"
#include <stdlib.h>
#include <stdio.h>

FILE *stream;

typedef enum {
    KW_ELSE,
    KW_IF,
    KW_INT,
    KW_RETURN,
    KW_VOID,
    KW_WHILE,
    KW_FLOAT,
    KW_STRING,
    //KW_FOR,
    KW_FUNCTION,
    KW_NULL,
    //KW_GLOBAL,
    //KW_BOOLEAN,
}Keyword;

typedef union {
    Keyword keyword;
    char *identifier;
    char *string;
    double number;
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
    //T_INCREMENT,
    T_MINUS,
    //T_DECREMENT,
    T_MULTIPLY,
    //T_MULTIPLY_ASSIGN,
    T_DIVIDE,
    //T_DIVIDE_ASSIGN,
    T_LESS,
    T_LESS_EQUAL,
    T_GREATER,
    T_GREATER_EQUAL,
    T_EQUAL,
    T_NOT_EQUAL,
    T_CONCATENATE,
    //T_CONCATENATE_ASSIGN,
    T_ASSIGN,
    T_SEMICOLON,
    T_COMMA,
    T_DOUBLE_DOT,
    T_LEFT_BRACKET,
    T_RIGHT_BRACKET,
    T_LEFT_BRACE,
    T_RIGHT_BRACE,
    //T_LEFT_SQUARE_BRACKET,
    //T_RIGHT_SQUARE_BRACKET,
    T_AND,
    T_OR,
    T_EOF,
    T_ERROR,
}Type;

typedef struct {
    Value value;
    Type type;
    int line;
    int column;
}Token;

int get_token(Token *token);

#endif //IFJ_SCANNER_H

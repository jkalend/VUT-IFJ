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
#include <stdbool.h>

FILE *stream;

typedef enum {
    KW_ELSE,
    KW_FLOAT,
    // please do not reorder
    KW_IF,
    KW_WHILE,
    KW_RETURN,
    KW_FUNCTION,
    KW_GLOBAL,
    
    KW_INT,
    KW_NULL,
    
    KW_STRING,
    KW_VOID,
    
    //KW_FOR,
    
    KW_BOOLEAN,
    KW_TRUE,
    KW_FALSE,
}Keyword;

typedef union {
	Keyword keyword;
	char *identifier;
	char *string;
	double number_float;
	long long number_int;
} Value;

typedef enum {
    T_VALID,
    T_IDENTIFIER,
    T_KEYWORD,

    T_DOUBLE_DOT,
    T_LEFT_BRACE,
    T_RIGHT_BRACE,
    
    T_DIVIDE,
    
    T_VAR,
    T_TYPE,
    T_SEMICOLON,
    T_ASSIGN,
    T_COMMA,
    T_EOF,
    T_END,

    T_RIGHT_BRACKET,

    T_STRING,
    T_INT,
    T_FLOAT,
    T_LEFT_BRACKET,

    T_PLUS,
    T_MINUS,
    T_MULTIPLY,
    T_LESS,
    T_LESS_EQUAL,
    T_GREATER,
    T_GREATER_EQUAL,
    T_EQUAL,
    T_NOT_EQUAL,
    T_CONCATENATE,
    T_AND,
    T_OR,
    T_NOT,
    
    
    T_ERROR,
    
}Type;

//int strict_type = true
//?int strict_type = false
typedef struct {
    Value value;
    Type type;
    int line;
	bool strict_type;
}Token;

typedef struct {
	int line;
	int first_read;
	int prologue_r;
}scanner_t;

int get_token(Token*, scanner_t*);
char* convert_string_for_ifjcode(char*, int);
int convert_esc_to_int(const char*, int);
int kw_check(const char*, Token*);

#endif	//IFJ_SCANNER_H

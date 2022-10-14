//Hello how are you this beautiful day? no krasne mi je

#include "scanner.h"
#define LEX_OK 0
#define LEX_ERROR 1
#define true 1

int get_token(Token *token) {
    while(true) {
        int c = fgetc(stream);
        if (c == EOF) {
            token->type = T_EOF;
            return 0;
        }
        if(isspace(c) != 0){
            continue;
        }
        switch (c) {
            case '/': {
                int c2 = fgetc(stream);
                if (c2 == '/') {
                    while (c2 != '\n') {
                        c2 = fgetc(stream);
                        if (c2 == EOF) {
                            token->type = T_EOF;
                            return 0;
                        }
                    }
                } else if (c2 == '*') {
                    c2 = fgetc(stream);
                    kokocina:
                    while (c2 != '*') {
                        c2 = fgetc(stream);
                        if (c2 == EOF) {
                            token->type = T_EOF;
                            return LEX_ERROR;
                        }
                    }
                    c2 = fgetc(stream);
                    if (c2 == '/') {
                        break;
                    } else {
                        goto kokocina;
                    }
                } else {
                    ungetc(c2, stream);
                    token->type = T_DIVIDE;
                    return 0;
                }
            }
            default: return LEX_ERROR;
        }
    }
}


long long convert_str_to_int(char *s){
    long long result = 0;
    result = strtoll(s, NULL, 10);
    return result;
}

double convert_str_to_float(char *s){
    double result = 0;
    result = strtod(s, NULL);
    return result;
}

int free_memory(char *s, int ret_code){
    free(s);
    return ret_code;
}

int kw_check(char *s){
    if (strcmp(s, "else") == 0) {
        return KW_ELSE;
    }
    if (strcmp(s, "float") == 0) {
        return KW_FLOAT;
    }
    if (strcmp(s, "function") == 0) {
        return KW_FUNCTION;
    }
    if (strcmp(s, "if") == 0) {
        return KW_IF;
    }
    if (strcmp(s, "int") == 0) {
        return KW_INT;
    }
    if (strcmp(s, "null") == 0) {
        return KW_NULL;
    }
    if (strcmp(s, "return") == 0) {
        return KW_RETURN;
    }
    if (strcmp(s, "string") == 0) {
        return KW_STRING;
    }
    if (strcmp(s, "void") == 0) {
        return KW_VOID;
    }
    if (strcmp(s, "while") == 0) {
        return KW_WHILE;
    }
    return 0;
}

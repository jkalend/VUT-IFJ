//Hello how are you this beautiful day? no krasne mi je

#include "scanner.h"
#define LEX_OK 0
#define LEX_ERROR 1
#define true 1

int get_token(Token *token) {
    if (first_read == 0){
        int c = fgetc(stream);
        if (c != '<'){
            token->type = T_ERROR;
            token->line = line;
            token->column[0] = column;
            token->column[1] = column + 1;
            return LEX_ERROR;
        }
        first_read = 1;
    }
    while(true) {
        int c = fgetc(stream);
        column++;
        if(c == '\n') {
            line++;
            column = 0;
            continue;
        }
        if(isspace(c) != 0){
            continue;
        }
        switch (c) {
            case EOF: {
                token->type = T_EOF;
                return LEX_OK;
            }
            case '/': {
                int c2 = fgetc(stream);
                column++;
                if (c2 == '/') {
                    while (c2 != '\n') {
                        c2 = fgetc(stream);
                        column++;
                        if (c2 == EOF) {
                            token->type = T_EOF;
                            token->line = line;
                            token->column[0] = column;
                            token->column[1] = column + 1;
                            return LEX_OK;
                        }
                    }
                    column = 0;
                    break;
                } else if (c2 == '*') {
                    c2 = fgetc(stream);
                    column++;
                    kokocina:
                    while (c2 != '*') {
                        c2 = fgetc(stream);
                        column++;
                        if(c2 == '\n') {
                            line++;
                            column = 0;
                        }
                        if (c2 == EOF) {
                            token->type = T_EOF;
                            token->line = line;
                            token->column[0] = column;
                            token->column[1] = column + 1;
                            return LEX_OK;
                        }
                    }
                    c2 = fgetc(stream);
                    column++;
                    if (c2 == EOF) {
                        token->type = T_EOF;
                        token->line = line;
                        token->column[0] = column;
                        token->column[1] = column + 1;
                        return LEX_OK;
                    }else if (c2 == '/') {
                        break;
                    } else {
                        if(c2 == '\n') {
                            line++;
                            column = 0;
                        }
                        goto kokocina;
                    }
                } else {
                    ungetc(c2, stream);
                    column--;
                    token->type = T_DIVIDE;
                    token->line = line;
                    token->column[0] = column;
                    token->column[1] = column + 1;
                    return LEX_OK;
                }
            }
            case '+': {
                token->type = T_PLUS;
                token->line = line;
                token->column[0] = column;
                token->column[1] = column + 1;
                return LEX_OK;
            }
            case '-': {
                token->type = T_MINUS;
                token->line = line;
                token->column[0] = column;
                token->column[1] = column + 1;
                return LEX_OK;
            }
            case '*': {
                token->type = T_MULTIPLY;
                token->line = line;
                token->column[0] = column;
                token->column[1] = column + 1;
                return LEX_OK;
            }
            case '<': { //TODO
                int c2 = fgetc(stream);
                column++;
                if (c2 == '=') {
                    token->type = T_LESS_EQUAL;
                    token->line = line;
                    token->column[0] = column - 1;
                    token->column[1] = column + 1;
                    return LEX_OK;
                } else if (c2 == '?'){
                    c2 = fgetc(stream);
                    column++;
                    if (c2 == 'p'){
                        c2 = fgetc(stream);
                        column++;
                        if (c2 == 'h'){
                            c2 = fgetc(stream);
                            column++;
                            if (c2 == 'p'){
                                char *arr = malloc(24);
                                char *slider = arr;
                                while(true) {
                                    c2 = fgetc(stream);
                                    column++;
                                    if (c2 == '\n') {
                                        line++;
                                        column = 0;
                                        continue;
                                    }
                                    if (isspace(c) != 0) {
                                        continue;
                                    }
                                    switch (c2) {
                                        case EOF: {
                                            token->type = T_ERROR;
                                            return LEX_ERROR;
                                        }
                                        case '/': {
                                            c2 = fgetc(stream);
                                            column++;
                                            if (c2 == '/') {
                                                while (c2 != '\n') {
                                                    c2 = fgetc(stream);
                                                    column++;
                                                    if (c2 == EOF) {
                                                        token->type = T_ERROR;
                                                        token->line = line;
                                                        token->column[0] = column;
                                                        token->column[1] = column + 1;
                                                        return LEX_ERROR;
                                                    }
                                                }
                                                column = 0;
                                                break;
                                            } else if (c2 == '*') {
                                                c2 = fgetc(stream);
                                                column++;
                                                loop:
                                                while (c2 != '*') {
                                                    c2 = fgetc(stream);
                                                    column++;
                                                    if (c2 == '\n') {
                                                        line++;
                                                        column = 0;
                                                    }
                                                    if (c2 == EOF) {
                                                        token->type = T_ERROR;
                                                        token->line = line;
                                                        token->column[0] = column;
                                                        token->column[1] = column + 1;
                                                        return LEX_ERROR;
                                                    }
                                                }
                                                c2 = fgetc(stream);
                                                column++;
                                                if (c2 == EOF) {
                                                    token->type = T_ERROR;
                                                    token->line = line;
                                                    token->column[0] = column;
                                                    token->column[1] = column + 1;
                                                    return LEX_OK;
                                                } else if (c2 == '/') {
                                                    break;
                                                } else {
                                                    if (c2 == '\n') {
                                                        line++;
                                                        column = 0;
                                                    }
                                                    goto loop;
                                                }
                                            }else{
                                                token->type = T_ERROR;
                                                token->line = line;
                                                token->column[0] = column;
                                                token->column[1] = column + 1;
                                                return LEX_ERROR;
                                            }
                                        }
                                        case 'd':{//TODO pouzij GOTO (mozna?)
                                            ungetc(c, stream);
                                            fgets(arr, 8, stream);
                                            slider = slider + 7;
                                            column = column + 7;
                                            if (strcmp(arr, "declare") != 0) {
                                                token->type = T_ERROR;
                                                token->line = line;
                                                token->column[0] = column - 7;
                                                token->column[1] = column + 1;
                                                return LEX_ERROR;
                                            }
                                            break;
                                        }
                                        case '(': case '=': case '1':{
                                            slider[0] = (char) c2;
                                            slider++;
                                            break;
                                        }
                                        case 's':{
                                            ungetc(c, stream);
                                            fgets(slider, 13, stream);
                                            column = column + 12;
                                            if (strcmp(arr, "strict_types") != 0) {
                                                token->type = T_ERROR;
                                                token->line = line;
                                                token->column[0] = column - 12;
                                                token->column[1] = column + 1;
                                                return LEX_ERROR;
                                            }
                                            slider = slider + 12;
                                            break;
                                        }
                                        case ')':{
                                            slider[0] = (char) c2;
                                            arr[23] = '\0';
                                            break;
                                        }
                                        case ';':{
                                            if(strcmp(arr, "declare(strict_types=1)") == 0) {
                                                token->type = T_VALID;
                                                token->line = line;
                                                token->column[0] = column - 23;
                                                token->column[1] = column + 1;
                                                return LEX_OK;
                                            }else{
                                                token->type = T_ERROR;
                                                token->line = line;
                                                token->column[0] = column - 23;
                                                token->column[1] = column + 1;
                                                return LEX_ERROR;
                                            }
                                        }
                                        default:{
                                            token->type = T_ERROR;
                                            token->line = line;
                                            token->column[0] = column - 23;
                                            token->column[1] = column + 1;
                                            return LEX_ERROR;
                                        }
                                    }
                                }
                            }else{
                                token->type = T_ERROR;
                                token->line = line;
                                token->column[0] = column;
                                token->column[1] = column + 1;
                                return LEX_ERROR;
                            }
                        }else{
                            token->type = T_ERROR;
                            token->line = line;
                            token->column[0] = column;
                            token->column[1] = column + 1;
                            return LEX_ERROR;
                        }
                    }else{
                        token->type = T_ERROR;
                        token->line = line;
                        token->column[0] = column;
                        token->column[1] = column + 1;
                        return LEX_ERROR;
                    }
                }
                else {
                    ungetc(c2, stream);
                    column--;
                    token->type = T_LESS;
                    token->line = line;
                    token->column[0] = column;
                    token->column[1] = column + 1;
                    return LEX_OK;
                }
            }
            case '>': {
                int c2 = fgetc(stream);
                column++;
                if (c2 == '=') {
                    token->type = T_GREATER_EQUAL;
                    token->line = line;
                    token->column[0] = column - 1;
                    token->column[1] = column + 1;
                    return LEX_OK;
                }
                else {
                    ungetc(c2, stream);
                    column--;
                    token->type = T_GREATER;
                    token->line = line;
                    token->column[0] = column;
                    token->column[1] = column + 1;
                    return LEX_OK;
                }
            }
            case '=': {
                int c2 = fgetc(stream);
                column++;
                if(c2 == '=') {
                    c2 = fgetc(stream);
                    column++;
                    if (c2 == '=') {
                        token->type = T_EQUAL;
                        token->line = line;
                        token->column[0] = column - 2;
                        token->column[1] = column + 1;
                        return LEX_OK;
                    }else{
                        token->type = T_ERROR;
                        token->line = line;
                        token->column[0] = column - 2;
                        token->column[1] = column;
                        return LEX_ERROR;
                    }
                } else {
                    ungetc(c2, stream);
                    column--;
                    token->type = T_ASSIGN;
                    token->line = line;
                    token->column[0] = column;
                    token->column[1] = column + 1;
                    return LEX_OK;
                }
            }
            case '!': {
                int c2 = fgetc(stream);
                column++;
                if(c2 == '=') {
                    c2 = fgetc(stream);
                    column++;
                    if (c2 == '=') {
                        token->type = T_NOT_EQUAL;
                        token->line = line;
                        token->column[0] = column - 2;
                        token->column[1] = column + 1;
                        return LEX_OK;
                    }else{
                        token->type = T_ERROR;
                        token->line = line;
                        token->column[0] = column - 2;
                        token->column[1] = column;
                        return LEX_ERROR;
                    }
                } else {
                    ungetc(c2, stream);
                    column--;
                    token->type = T_NOT;
                    token->line = line;
                    token->column[0] = column;
                    token->column[1] = column + 1;
                    return LEX_OK;
                }
            }
            case '(': {
                token->type = T_LEFT_BRACKET;
                token->line = line;
                token->column[0] = column;
                token->column[1] = column + 1;
                return LEX_OK;
            }
            case ')': {
                token->type = T_RIGHT_BRACKET;
                token->line = line;
                token->column[0] = column;
                token->column[1] = column + 1;
                return LEX_OK;
            }
            case ',': {
                token->type = T_COMMA;
                token->line = line;
                token->column[0] = column;
                token->column[1] = column + 1;
                return LEX_OK;
            }
            case ';': {
                token->type = T_SEMICOLON;
                token->line = line;
                token->column[0] = column;
                token->column[1] = column + 1;
                return LEX_OK;
            }
            case '{': {
                token->type = T_LEFT_BRACE;
                token->line = line;
                token->column[0] = column;
                token->column[1] = column + 1;
                return LEX_OK;
            }
            case '}': {
                token->type = T_RIGHT_BRACE;
                token->line = line;
                token->column[0] = column;
                token->column[1] = column + 1;
                return LEX_OK;
            }
            case '.': {
                token->type = T_CONCATENATE;
                token->line = line;
                token->column[0] = column;
                token->column[1] = column + 1;
                return LEX_OK;
            }
            case '&': {
                int c2 = fgetc(stream);
                column++;
                if (c2 == '&') {
                    token->type = T_AND;
                    token->line = line;
                    token->column[0] = column;
                    token->column[1] = column + 1;
                    return LEX_OK;
                } else {
                    ungetc(c2, stream);
                    column--;
                    token->type = T_ERROR;
                    token->line = line;
                    token->column[0] = column;
                    token->column[1] = column + 1;
                    return LEX_ERROR;
                }
            }
            case '|': {
                int c2 = fgetc(stream);
                column++;
                if (c2 == '|') {
                    token->type = T_OR;
                    token->line = line;
                    token->column[0] = column;
                    token->column[1] = column + 1;
                    return LEX_OK;
                } else {
                    ungetc(c2, stream);
                    column--;
                    token->type = T_ERROR;
                    token->line = line;
                    token->column[0] = column;
                    token->column[1] = column + 1;
                    return LEX_ERROR;
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
    if (strcmp(s, "boolean") == 0) {
        return KW_BOOLEAN;
    }
    if (strcmp(s, "true") == 0) {
        return KW_TRUE;
    }
    if (strcmp(s, "false") == 0) {
        return KW_FALSE;
    }
    return 0;
}

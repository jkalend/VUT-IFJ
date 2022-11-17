
#include "scanner.h"
#define LEX_OK 0
#define true 1

int line = 1;
int first_read = 0;

int get_token(Token *token) {
    if (first_read == 0){
        int c = fgetc(stream);
        if (c != '<'){
            token->type = T_ERROR;
            token->line = line;
            return BAD_LEXEM;
        }
        first_read = 1;
        ungetc(c, stream);
    }
    while(true) {
        int c = fgetc(stream);
        if(c == '\n') {
            line++;
            continue;
        }
        if(isspace(c)){
            continue;
        }
        if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_') {
            int size = 40;
            int i = 0;
            char *identifier = malloc(size * sizeof(char));
			if(identifier == NULL){
				exit(BAD_INTERNAL);
			}
            while(c != EOF && (isalnum(c) || c == '_')) {
                if(i == size) {
                    size *= 2;
					char *tmp = realloc(identifier, size * sizeof(char));
					if(tmp == NULL){
						free(identifier);
						exit(BAD_INTERNAL);
					}
					identifier = tmp;
                }
                identifier[i] = (char) c;
                i++;
                c = fgetc(stream);
            }
            ungetc(c, stream);
            identifier[i] = '\0';
            if (kw_check(identifier, token) != 1){
                token->line = line;
                free_memory(identifier, LEX_OK);
                return LEX_OK;
            }
            token->type = T_IDENTIFIER;
            token->value.identifier = identifier;
            token->line = line;
            return LEX_OK;
        }
        if(c >= '0' && c <= '9'){
            int size = 40;
            char *str = malloc(size);
			if(str == NULL){
				exit(BAD_INTERNAL);
			}
            int i = 0;
            int e = 0;
            int plus_minus = 0;
            int dot = 0;
            while ((c >= '0' && c <= '9') || c == '.' || c == 'e' || c == 'E' || c == '+' || c == '-'){
                if (i == size - 10) {
                    size *= 2;
                    char *tmp = realloc(str, size);
					if(tmp == NULL){
						free(str);
						exit(BAD_INTERNAL);
					}
					str = tmp;
                }
                str[i] = (char) c;
                i++;
                c = fgetc(stream);
				if((str[i-1] >= '0' && str[i-1] <= '9') && (c == '+' || c == '-')){
					break;
				}
            }
            ungetc(c, stream);
            str[i] = '\0';
            i = 0;
            while (str[i] != '\0'){
                if (str[i] == '.'){
                    dot++;
                }
                if (str[i] == 'e' || str[i] == 'E'){
                    e++;
                }
                if (str[i] == '+' || str[i] == '-'){
                    plus_minus++;
                }
                i++;
            }
            if(dot == 0 && e == 0 && plus_minus == 0){
                token->type = T_INT;
                token->value.number_int = strtoll(str, NULL, 10);
                token->line = line;
                free(str);
                return LEX_OK;
            }else if((dot == 1 && e == 0 && plus_minus == 0) ||
					(dot == 1 && e == 1 && plus_minus == 1) ||
					(dot == 0 && e == 1 && plus_minus == 1) ||
					(dot == 0 && e == 1 && plus_minus == 0)) {
                token->type = T_FLOAT;
                token->value.number_float = strtod(str, NULL);
                token->line = line;
                free(str);
                return LEX_OK;
            }else{
                token->type = T_ERROR;
                token->line = line;
                free(str);
                return BAD_LEXEM;
            }
        }
        switch (c) {
            case EOF: {
                token->type = T_EOF;
                return LEX_OK;
            }
            case '/': {
                int c2 = fgetc(stream);
                if (c2 == '/') {
                    while (c2 != '\n') {
                        c2 = fgetc(stream);
                        if (c2 == EOF) {
                            token->type = T_EOF;
                            token->line = line;
                            return LEX_OK;
                        }
                    }
                    break;
                } else if (c2 == '*') {
                    c2 = fgetc(stream);

                    kokocina:
                    while (c2 != '*') {
                        c2 = fgetc(stream);
                        if(c2 == '\n') {
                            line++;
                        }
                        if (c2 == EOF) {
                            token->type = T_EOF;
                            token->line = line;
                            return LEX_OK;
                        }
                    }
                    c2 = fgetc(stream);
                    if (c2 == EOF) {
                        token->type = T_EOF;
                        token->line = line;
                        return LEX_OK;
                    }else if (c2 == '/') {
                        break;
                    } else {
                        if(c2 == '\n') {
                            line++;
                        }
                        goto kokocina;
                    }
                } else {
                    ungetc(c2, stream);

                    token->type = T_DIVIDE;
                    token->line = line;
                    return LEX_OK;
                }
            }
            case '+': {
                token->type = T_PLUS;
                token->line = line;
                return LEX_OK;
            }
            case '-': {
                token->type = T_MINUS;
                token->line = line;
                return LEX_OK;
            }
            case '*': {
                token->type = T_MULTIPLY;
                token->line = line;
                return LEX_OK;
            }
            case '<': {
                int c2 = fgetc(stream);
                if (c2 == '=') {
                    token->type = T_LESS_EQUAL;
                    token->line = line;
                    return LEX_OK;
                } else if (c2 == '?'){
                    c2 = fgetc(stream);
                    if (c2 == 'p'){
                        c2 = fgetc(stream);
                        if (c2 == 'h'){
                            c2 = fgetc(stream);
                            if (c2 == 'p'){
								int ok = 0;
								char *arr = malloc(24);
								if(arr == NULL){
									exit(BAD_INTERNAL);
								}
								char *slider = arr;
								while (true) {
									c2 = fgetc(stream);
									if (c2 == '\n') {
										line++;
										ok = 1;
										continue;
									}
									if (isspace(c2)) {
										ok = 1;
										continue;
									}
									switch (c2) {
										case '/': {
											c2 = fgetc(stream);
											if (c2 == '/') {
												ok = 1;
												while (c2 != '\n') {
													c2 = fgetc(stream);
													if (c2 == EOF) {
														token->type = T_ERROR;
														token->line = line;
														return BAD_LEXEM;
													}
												}
												break;
											} else if (c2 == '*') {
												ok = 1;
												c2 = fgetc(stream);
											loop:
												while (c2 != '*') {
													c2 = fgetc(stream);

													if (c2 == '\n') {
														line++;
													}
													if (c2 == EOF) {
														token->type = T_ERROR;
														token->line = line;
														return BAD_LEXEM;
													}
												}
												c2 = fgetc(stream);
												if (c2 == EOF) {
													token->type = T_ERROR;
													token->line = line;
													return LEX_OK;
												} else if (c2 == '/') {
													break;
												} else {
													if (c2 == '\n') {
														line++;
													}
													goto loop;
												}
											} else {
												token->type = T_ERROR;
												token->line = line;
												return BAD_LEXEM;
											}
										}
										case 'd': {
											if(ok == 0){
												token->type = T_ERROR;
												token->line = line;
												return BAD_LEXEM;
											}
											ungetc(c2, stream);
											fgets(arr, 8, stream);
											slider = slider + 7;
											if (strcmp(arr, "declare") != 0) {
												token->type = T_ERROR;
												token->line = line;
												return BAD_LEXEM;
											}
											break;
										}
										case '(':
										case '=':
										case '1': {
											slider[0] = (char)c2;
											slider++;
											break;
										}
										case 's': {
											ungetc(c2, stream);
											fgets(slider, 13, stream);
											if (strcmp(slider, "strict_types") != 0) {
												token->type = T_ERROR;
												token->line = line;
												return BAD_LEXEM;
											}
											slider = slider + 12;
											break;
										}
										case ')': {
											slider[0] = (char)c2;
											arr[23] = '\0';
											break;
										}
										case ';': {
											if (strcmp(arr, "declare(strict_types=1)") == 0) {
												token->type = T_VALID;
												token->line = line;
												free_memory(arr, LEX_OK);
												return LEX_OK;
											} else {
												token->type = T_ERROR;
												token->line = line;
												free_memory(arr, BAD_LEXEM);
												return BAD_LEXEM;
											}
										}
										default: {
											token->type = T_ERROR;
											token->line = line;
											return BAD_LEXEM;
										}
									}
								}
                            }else{
                                token->type = T_ERROR;
                                token->line = line;
                                return BAD_LEXEM;
                            }
                        }else{
                            token->type = T_ERROR;
                            token->line = line;
                            return BAD_LEXEM;
                        }
                    }else{
                        token->type = T_ERROR;
                        token->line = line;
                        return BAD_LEXEM;
                    }
                }
                else {
                    ungetc(c2, stream);
                    token->type = T_LESS;
                    token->line = line;
                    return LEX_OK;
                }
            }
            case '>': {
                int c2 = fgetc(stream);
                if (c2 == '=') {
                    token->type = T_GREATER_EQUAL;
                    token->line = line;
                    return LEX_OK;
                }
                else {
                    ungetc(c2, stream);
                    token->type = T_GREATER;
                    token->line = line;
                    return LEX_OK;
                }
            }
            case '=': {
                int c2 = fgetc(stream);
                if(c2 == '=') {
                    c2 = fgetc(stream);
                    if (c2 == '=') {
                        token->type = T_EQUAL;
                        token->line = line;
                        return LEX_OK;
                    }else{
                        token->type = T_ERROR;
                        token->line = line;
                        return BAD_LEXEM;
                    }
                } else {
                    ungetc(c2, stream);
                    token->type = T_ASSIGN;
                    token->line = line;
                    return LEX_OK;
                }
            }
            case '!': {
                int c2 = fgetc(stream);
                if(c2 == '=') {
                    c2 = fgetc(stream);
                    if (c2 == '=') {
                        token->type = T_NOT_EQUAL;
                        token->line = line;
                        return LEX_OK;
                    }else{
                        token->type = T_ERROR;
                        token->line = line;
                        return BAD_LEXEM;
                    }
                } else {
                    token->type = T_ERROR;
                    token->line = line;
                    return BAD_LEXEM;
                }
            }
            case '(': {
                token->type = T_LEFT_BRACKET;
                token->line = line;
                return LEX_OK;
            }
            case ')': {
                token->type = T_RIGHT_BRACKET;
                token->line = line;
                return LEX_OK;
            }
            case ',': {
                token->type = T_COMMA;
                token->line = line;
                return LEX_OK;
            }
            case ';': {
                token->type = T_SEMICOLON;
                token->line = line;
                return LEX_OK;
            }
            case '{': {
                token->type = T_LEFT_BRACE;
                token->line = line;
                return LEX_OK;
            }
            case '}': {
                token->type = T_RIGHT_BRACE;
                token->line = line;
                return LEX_OK;
            }
            case '.': {
                token->type = T_CONCATENATE;
                token->line = line;
                return LEX_OK;
            }
            /*
            case '&': {
                int c2 = fgetc(stream);
                if (c2 == '&') {
                    token->type = T_AND;
                    token->line = line;
                    return LEX_OK;
                } else {
                    ungetc(c2, stream);
                    token->type = T_ERROR;
                    token->line = line;
                    return BAD_LEXEM;
                }
            }
            case '|': {
                int c2 = fgetc(stream);
                if (c2 == '|') {
                    token->type = T_OR;
                    token->line = line;
                    return LEX_OK;
                } else {
                    ungetc(c2, stream);
                    token->type = T_ERROR;
                    token->line = line;
                    return BAD_LEXEM;
                }
            }
            */
            case ':':{
                token->type = T_DOUBLE_DOT;
                token->line = line;
                return LEX_OK;
            }
            case '$':{
                token->type = T_VAR;
                token->line = line;
                int c2 = fgetc(stream);
                if(c2 != '_' && (c2 <'A' || (c2 > 'Z' && c2 < 'a') || c2 > 'z')){
                    token->type = T_ERROR;
                    token->line = line;
                    return BAD_LEXEM;
                }
                int size = 40;
                char *str = malloc(40);
				if(str == NULL){
					exit(BAD_INTERNAL);
				}
                int i = 0;
                while((c2 == '_') || (c2 >= '0' && c2 <= '9') || (c2 >= 'A' && c2 <= 'Z') || (c2 >= 'a' && c2 <= 'z')){
                    if(i == size - 10){
                        size *= 2;
                        char *tmp = realloc(str, size);
						if(tmp == NULL){
							free(str);
							exit(BAD_INTERNAL);
						}
						str = tmp;
                    }
                    str[i] = (char) c2;
                    i++;
                    c2 = fgetc(stream);
                }
                ungetc(c2, stream);
                str[i] = '\0';
                if (kw_check(str, token) != 1){
                    token->line = line;
                    free_memory(str, LEX_OK);
                    return LEX_OK;
                }
                token->value.identifier = str;
                return LEX_OK;
            }
            case '?': {
                int c2 = fgetc(stream);
                if (c2 == '>') {
                    token->type = T_END;
                    token->line = line;
                    return LEX_OK;
                } else if (c2 >= 'a' && c2 <= 'z') {
                    char *str = malloc(40);
					if(str == NULL){
						exit(BAD_INTERNAL);
					}
                    int size = 40;
                    int i = 0;
                    while (c2 >= 'a' && c2 <= 'z') {
                        if (i == size - 10) {
                            size *= 2;
                            char *tmp = realloc(str, size);
							if(tmp == NULL){
								free(str);
								exit(BAD_INTERNAL);
							}
							str = tmp;
                        }
                        str[i] = (char) c2;
                        i++;
                        c2 = fgetc(stream);
                    }
                    ungetc(c2, stream);
                    str[i] = '\0';
                    if (kw_check(str, token) != 2) {
                        token->type = T_ERROR;
                        token->line = line;
                        free(str);
                        return BAD_LEXEM;
                    }
                    token->line = line;
                    return LEX_OK;

                } else {
                    token->type = T_ERROR;
                    token->line = line;
                    return BAD_LEXEM;
                }
            }
            case '"': {
                token->type = T_STRING;
                token->line = line;
                int c2 = fgetc(stream);
                if(c2 == '"'){
                    token->value.string = "";
                    return LEX_OK;
                }
                char *str = malloc(40);
				if(str == NULL){
					exit(BAD_INTERNAL);
				}
                int size = 40;
                int i = 0;
                while (true) {
                    if (i == size - 10) {
                        size *= 2;
                        char *tmp = realloc(str, size);
						if(tmp == NULL){
							free(str);
							exit(BAD_INTERNAL);
						}
						str = tmp;
                    }
                    str[i] = (char) c2;
                    i++;
                    if(c2 == '\''){
                        c2 = fgetc(stream);
                        str[i] = (char) c2;
                        i++;
                    }
                    c2 = fgetc(stream);
                    if (c2 == '"') {
                        str[i] = '\0';
                        break;
                    }else if(c2 == EOF){
                        token->type = T_ERROR;
                        token->line = line;
                        free(str);
                        return BAD_LEXEM;
                    }
                }
                token->value.string = convert_string_for_ifjcode(str);
                return LEX_OK;
            }
            default: {
                token->type = T_ERROR;
                token->line = line;
                return BAD_LEXEM;
            }
        }
    }
}

char* convert_string_for_ifjcode(char *str) {
    int i = 0;
    unsigned long len = strlen(str);
    char hex[2];
    char oct[3];
    while(str[i] != '\0'){
		if(str[i] == '\\' && str[i+1] == 'x'){
			hex[0] = str[i+2];
			hex[1] = str[i+3];
			if(convert_esc_to_char(hex, 16) == -1){
				i++;
				continue;
			}
			str[i] = convert_esc_to_char(hex, 2);
			int j = i;
			while(j < (int) len - 4){
				str[j+1] = str[j+4];
				j++;
			}
		}else if(str[i] == '\\' && ((str[i+1] >= '0' && str[i+1] <= '3') && (str[i+2] >= '0' && str[i+2] <= '7') && (str[i+3] >= '0' && str[i+3] <= '7'))){
			oct[0] = str[i+1];
			oct[1] = str[i+2];
			oct[2] = str[i+3];
			if(convert_esc_to_char(oct, 8) == -1){
				i++;
				continue;
			}
			str[i] = convert_esc_to_char(oct, 3);
			int j = i;
			while (j < (int) len - 4) {
				str[j+1] = str[j+4];
				j++;
			}
		}else if(str[i] == '\\'){
			int j = i;
			switch (str[i+1]) {
				case 'n':
					str[i] = '\n';
					while (j < (int) len - 2) {
						str[j + 1] = str[j + 2];
						j++;
					}
					break;
				case 't':
					str[i] = '\t';
					while (j < (int) len - 2) {
						str[j + 1] = str[j + 2];
						j++;
					}
					break;
				case 'r':
					str[i] = '\r';
					while (j < (int) len - 2) {
						str[j + 1] = str[j + 2];
						j++;
					}
					break;
				case 'e':
					str[i] = 27;
					while (j < (int) len - 2) {
						str[j + 1] = str[j + 2];
						j++;
					}
					break;
				case 'a':
					str[i] = 7;
					while (j < (int) len - 2) {
						str[j + 1] = str[j + 2];
						j++;
					}
					break;
				case 'f':
					str[i] = '\f';
					while (j < (int) len - 2) {
						str[j + 1] = str[j + 2];
						j++;
					}
					break;
				case 'v':
					str[i] = '\v';
					while (j < (int) len - 2) {
						str[j + 1] = str[j + 2];
						j++;
					}
					break;
				case '\\':
					str[i] = '\\';
					while (j < (int) len - 2) {
						str[j + 1] = str[j + 2];
						j++;
					}
					break;
				case '$':
					str[i] = '$';
					while (j < (int) len - 2) {
						str[j + 1] = str[j + 2];
						j++;
					}
					break;
				default:
					break;
			}
		}
		i++;
    }
    return str;
}

char convert_esc_to_char(const char* str, int len) {
    long result = 0;
    if (len == 3) {
        result = strtol(str, NULL, 8);
        if(result > 255 || result == 36){
            return -1;
        }
    }else if(len == 2) {
        if(str[0] < '0' || (str[0] > '9' && str[0] < 'A') || (str[0] > 'F' && str[0] < 'a') || str[0] > 'f'){
            return -1;
        }
        if(str[1] < '0' || (str[1] > '9' && str[1] < 'A') || (str[1] > 'F' && str[1] < 'a') || str[1] > 'f' ){
            return -1;
        }
        result = strtol(str, NULL, 16);
        if(result == 36){
            return -1;
        }
    }
    return (char) result;
}

int free_memory(char *s, int ret_code){
    free(s);
    return ret_code;
}

int kw_check(char *s, Token *token){
    if (strcmp(s, "else") == 0) {
        token->type = T_KEYWORD;
        token->value.keyword = KW_ELSE;
        return LEX_OK;
    }
    if (strcmp(s, "float") == 0) {
        token->type = T_TYPE;
        token->value.keyword = KW_FLOAT;
        return 2;
    }
    if (strcmp(s, "function") == 0) {
        token->type = T_KEYWORD;
        token->value.keyword = KW_FUNCTION;
        return LEX_OK;
    }
    if (strcmp(s, "if") == 0) {
        token->type = T_KEYWORD;
        token->value.keyword = KW_IF;
        return LEX_OK;
    }
    if (strcmp(s, "int") == 0) {
        token->type = T_TYPE;
        token->value.keyword = KW_INT;
        return 2;
    }
    if (strcmp(s, "null") == 0) {
        token->type = T_KEYWORD;
        token->value.keyword = KW_NULL;
        return LEX_OK;
    }
    if (strcmp(s, "return") == 0) {
        token->type = T_KEYWORD;
        token->value.keyword = KW_RETURN;
        return LEX_OK;
    }
    if (strcmp(s, "string") == 0) {
        token->type = T_TYPE;
        token->value.keyword = KW_STRING;
        return 2;
    }
    if (strcmp(s, "void") == 0) {
        token->type = T_TYPE;
        token->value.keyword = KW_VOID;
        return LEX_OK;
    }
    if (strcmp(s, "while") == 0) {
        token->type = T_KEYWORD;
        token->value.keyword = KW_WHILE;
        return LEX_OK;
    }
    if (strcmp(s, "global") == 0) {
        token->type = T_KEYWORD;
        token->value.keyword = KW_GLOBAL;
        return LEX_OK;
    }
    if (strcmp(s, "boolean") == 0) {
        token->type = T_KEYWORD;
        token->value.keyword = KW_BOOLEAN;
        return LEX_OK;
    }
    if (strcmp(s, "true") == 0) {
        token->type = T_KEYWORD;
        token->value.keyword = KW_TRUE;
        return LEX_OK;
    }
    if (strcmp(s, "false") == 0) {
        token->type = T_KEYWORD;
        token->value.keyword = KW_FALSE;
        return LEX_OK;
    }
    return BAD_LEXEM;
}

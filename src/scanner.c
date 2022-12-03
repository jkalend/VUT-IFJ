#include "scanner.h"
#define LEX_OK 0

/**
 * @brief function of lexical analyzator, modifies tokens
 * @param token token allocated by syntax analyzator, modified by scanner
 * @param scanner scanner structure to hold flags
 * @return returns 0 if everything is ok, otherwise returns 1
 */
int get_token(Token * restrict token, scanner_t * restrict scanner) {
	token->strict_type = true;
    if (scanner->first_read == 0){ //checking if there are no characters before prologue
        int c = fgetc(stream);
		if(c == EOF){ //empty file
			token->type = T_EOF;
			token->line = scanner->line;
			return LEX_OK;
		}else if (c != '<'){
            token->type = T_ERROR;
            token->line = scanner->line;
            return BAD_LEXEM;
        }
	scanner->first_read = 1;
	ungetc(c, stream);
    }
    while(true) {
		register int c = fgetc(stream);
        if(c == '\n') { //line increment
            scanner->line += 1;
            continue;
        }
        if(isspace(c)){ //skipping whitespaces
            continue;
        }
        if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_') { //identifier begins
            int size = 40;
            int i = 0;
            char *identifier = malloc(size * sizeof(char));
			if(identifier == NULL){
				exit(BAD_INTERNAL);
			}
			//read identifier and save as string variable
            while(c != EOF && (isalnum(c) || c == '_')) {
                if(i == (size / 2)) {
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
            if (kw_check(identifier, token) != 1){ //token is keyword
                token->line = scanner->line;
                free(identifier);
                return LEX_OK;
            }
            token->type = T_IDENTIFIER; //token is identifier
            token->value.identifier = identifier;
            token->line = scanner->line;
            return LEX_OK;
        }
        if(c >= '0' && c <= '9'){ //number begins
            int size = 40;
            char *str = malloc(size);
			if(str == NULL){
				exit(BAD_INTERNAL);
			}
            register int i = 0;
            int e = 0;
            int plus_minus = 0;
            int dot = 0;
			//read and save number as a string variable
            while ((c >= '0' && c <= '9') || c == '.' || c == 'e' || c == 'E' || c == '+' || c == '-'){
                if (i == (size / 2)) {
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
				//if there is sign following a number, reading ends
				if((str[i-1] >= '0' && str[i-1] <= '9') && (c == '+' || c == '-')){
					break;
				}
				if((c < '0' || c > '9') && (str[i-1] == '.')){ //if the following character after
															   //dot isn't number, error occurs
					token->type = T_ERROR;
					token->line = scanner->line;
					free(str);
					return BAD_LEXEM;
				}
            }
            ungetc(c, stream);
            str[i] = '\0';
			if(str[i-1] < '0' || str[i-1] > '9'){ //if last character isn't number, error occurs
				token->type = T_ERROR;
				token->line = scanner->line;
				free(str);
				return BAD_LEXEM;
			}
            i = 0;
            while (str[i] != '\0'){
                if (str[i] == '.'){
					if(e > 0){
						token->type = T_ERROR;
						token->line = scanner->line;
						free(str);
						return BAD_LEXEM;
					}
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
			//checking number format
            if(dot == 0 && e == 0 && plus_minus == 0){ //integer format
                token->type = T_INT;
                token->value.number_int = strtoll(str, NULL, 10); //conversion for
																				   //IFJcode22
                token->line = scanner->line;
                free(str);
                return LEX_OK;
				//possible float formats
            }else if((dot == 1 && e == 0 && plus_minus == 0) ||
					(dot == 1 && e == 1 && plus_minus == 1) ||
					(dot == 0 && e == 1 && plus_minus == 1) ||
					(dot == 0 && e == 1 && plus_minus == 0) ||
				    (dot == 1 && e == 1 && plus_minus == 0)) {
                token->type = T_FLOAT;
                token->value.number_float = strtod(str, NULL); //conversion for IFJcode22
                token->line = scanner->line;
                free(str);
                return LEX_OK;
            }else{
                token->type = T_ERROR;
                token->line = scanner->line;
                free(str);
                return BAD_LEXEM;
            }
        }
        switch (c) {
            case EOF: { //token is EOF
                token->type = T_EOF;
                return LEX_OK;
            }
            case '/': { //either token is divide or comment starts
                register int c2 = fgetc(stream);
                if (c2 == '/') {
                    while (c2 != '\n') {
                        c2 = fgetc(stream);
                        if (c2 == EOF) {
                            token->type = T_EOF;
                            token->line = scanner->line;
                            return LEX_OK;
                        }
                    }
                    break;
                } else if (c2 == '*') {
                    c2 = fgetc(stream);
                    commentary:
                    while (c2 != '*') {
                        c2 = fgetc(stream);
                        if(c2 == '\n') {
                            scanner->line += 1;
                        }
                        if (c2 == EOF) { //unterminated comment
                            exit(BAD_LEXEM);
                        }
                    }
                    c2 = fgetc(stream);
                    if (c2 == EOF) { //unterminated comment
                        exit(BAD_LEXEM);
                    }else if (c2 == '/') {
                        break;
                    } else { //* was found but / not, so go back
							 //to the while loop and search for next *
                        if(c2 == '\n') {
                            scanner->line += 1;
                        }
                        goto commentary;
                    }
                } else { //token is divide
                    ungetc(c2, stream);
                    token->type = T_DIVIDE;
                    token->line = scanner->line;
                    return LEX_OK;
                }
            }
            case '+': { //token is plus
                token->type = T_PLUS;
                token->line = scanner->line;
                return LEX_OK;
            }
            case '-': { //token is minus
                token->type = T_MINUS;
                token->line = scanner->line;
                return LEX_OK;
            }
            case '*': { //token is multiplication
                token->type = T_MULTIPLY;
                token->line = scanner->line;
                return LEX_OK;
            }
            case '<': { //token is less, less equal or valid
                register int c2 = fgetc(stream);
                if (c2 == '=') { //less equal
                    token->type = T_LESS_EQUAL;
                    token->line = scanner->line;
                    return LEX_OK;
                } else if (c2 == '?'){ //prologue
                    c2 = fgetc(stream);
                    if (c2 == 'p'){
                        c2 = fgetc(stream);
                        if (c2 == 'h'){
                            c2 = fgetc(stream);
                            if (c2 == 'p'){
								if(scanner->prologue_r == 1){ //repeating prologue
									exit(BAD_SYNTAX);
								}
								scanner->prologue_r = 1;
								int ok = 0;
								char *arr = malloc(24);
								if(arr == NULL){
									exit(BAD_INTERNAL);
								}
								char *slider = arr;
								while (true) { //this loop checks for "declare(strict_types=1); with
											   //possible whitespaces and/or comments in between
									c2 = fgetc(stream);
									if (c2 == '\n') {
										scanner->line += 1;
										ok = 1;
										continue;
									}
									if (isspace(c2)) {
										ok = 1;
										continue;
									}
									switch (c2) {
										case '/': { //comment somewhere inside declare
											c2 = fgetc(stream);
											if (c2 == '/') {
												ok = 1;
												while (c2 != '\n') {
													c2 = fgetc(stream);
													if (c2 == EOF) { //incomplete declare
														token->type = T_ERROR;
														token->line = scanner->line;
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
														scanner->line += 1;
													}
													if (c2 == EOF) { //incomplete declare
														exit(BAD_LEXEM);
													}
												}
												c2 = fgetc(stream);
												if (c2 == EOF) {
													exit(BAD_LEXEM); //incomplete declare
												} else if (c2 == '/') { //end of comment
													break;
												} else { //* was found but / not, so go back
														 //to the while loop and search for next *
													if (c2 == '\n') {
														scanner->line += 1;
													}
													goto loop; //
												}
											} else {
												token->type = T_ERROR;
												token->line = scanner->line;
												return BAD_LEXEM;
											}
										}
										case 'd': {
											if(ok == 0){ //if there is no whitespace or comment
														 //between <?php and declare, error occurs
												token->type = T_ERROR;
												token->line = scanner->line;
												return BAD_LEXEM;
											}
											ungetc(c2, stream);
											fgets(arr, 8, stream);
											slider = slider + 7;
											if (strcmp(arr, "declare") != 0) {
												token->type = T_ERROR;
												token->line = scanner->line;
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
												token->line = scanner->line;
												return BAD_LEXEM;
											}
											slider = slider + 12;
											break;
										}
										case ')': {
											slider[0] = (char)c2;
											arr[23] = '\0'; //insert terminating null
											break;
										}
										case ';': { //check if entire declare is correct, if so,
													//token is valid
											if (strcmp(arr, "declare(strict_types=1)") == 0) {
												token->type = T_VALID;
												token->line = scanner->line;
												free(arr);
												return LEX_OK;
											} else {
												token->type = T_ERROR;
												token->line = scanner->line;
												free(arr);
												return BAD_LEXEM;
											}
										}
										default: {
											token->type = T_ERROR;
											token->line = scanner->line;
											return BAD_LEXEM;
										}
									}
								}
                            }else{ //faulty prologue
                                token->type = T_ERROR;
                                token->line = scanner->line;
                                return BAD_LEXEM;
                            }
                        }else{ //faulty prologue
                            token->type = T_ERROR;
                            token->line = scanner->line;
                            return BAD_LEXEM;
                        }
                    }else{ //faulty prologue
                        token->type = T_ERROR;
                        token->line = scanner->line;
                        return BAD_LEXEM;
                    }
                }
                else { //token is less
                    ungetc(c2, stream);
                    token->type = T_LESS;
                    token->line = scanner->line;
                    return LEX_OK;
                }
            }
            case '>': { //token can be greater or greater equal
                int c2 = fgetc(stream);
                if (c2 == '=') {
                    token->type = T_GREATER_EQUAL;
                    token->line = scanner->line;
                    return LEX_OK;
                }
                else {
                    ungetc(c2, stream);
                    token->type = T_GREATER;
                    token->line = scanner->line;
                    return LEX_OK;
                }
            }
            case '=': { //token can be assignment or equal
                int c2 = fgetc(stream);
                if(c2 == '=') {
                    c2 = fgetc(stream);
                    if (c2 == '=') { // !== is matched, token is equal
                        token->type = T_EQUAL;
                        token->line = scanner->line;
                        return LEX_OK;
                    }else{ // != doesn't match any allowed format, hence error occurs
						ungetc(c2, stream);
                        token->type = T_ERROR;
                        token->line = scanner->line;
                        return BAD_LEXEM;
                    }
                } else { //if only one = is matched, token is assignment
                    ungetc(c2, stream);
                    token->type = T_ASSIGN;
                    token->line = scanner->line;
                    return LEX_OK;
                }
            }
            case '!': { //token can be not equal
                int c2 = fgetc(stream);
                if(c2 == '=') {
                    c2 = fgetc(stream);
                    if (c2 == '=') { //either !== is matched or error occurs
                        token->type = T_NOT_EQUAL;
                        token->line = scanner->line;
                        return LEX_OK;
                    }else{
						ungetc(c2, stream);
                        token->type = T_ERROR;
                        token->line = scanner->line;
                        return BAD_LEXEM;
                    }
                } else {
					ungetc(c2, stream);
                    token->type = T_ERROR;
                    token->line = scanner->line;
                    return BAD_LEXEM;
                }
            }
            case '(': { //token is opening parenthesis
                token->type = T_LEFT_BRACKET;
                token->line = scanner->line;
                return LEX_OK;
            }
            case ')': { //token is closing parenthesis
                token->type = T_RIGHT_BRACKET;
                token->line = scanner->line;
                return LEX_OK;
            }
            case ',': { //token is comma
                token->type = T_COMMA;
                token->line = scanner->line;
                return LEX_OK;
            }
            case ';': { //token is semicolon
                token->type = T_SEMICOLON;
                token->line = scanner->line;
                return LEX_OK;
            }
            case '{': { //token is opening brace
                token->type = T_LEFT_BRACE;
                token->line = scanner->line;
                return LEX_OK;
            }
            case '}': { //token is closing brace
                token->type = T_RIGHT_BRACE;
                token->line = scanner->line;
                return LEX_OK;
            }
            case '.': { //token is dot
                token->type = T_CONCATENATE;
                token->line = scanner->line;
                return LEX_OK;
            }
            case ':':{ //token is colon
                token->type = T_DOUBLE_DOT;
                token->line = scanner->line;
                return LEX_OK;
            }
            case '$':{ //token is variable
                token->type = T_VAR;
                token->line = scanner->line;
                register int c2 = fgetc(stream);
                if(c2 != '_' && (c2 <'A' || (c2 > 'Z' && c2 < 'a') || c2 > 'z')){
                    token->type = T_ERROR;
                    token->line = scanner->line;
                    return BAD_LEXEM;
                }
                int size = 40;
                char *str = malloc(40);
				if(str == NULL){
					exit(BAD_INTERNAL);
				}
                int i = 0;
                while((c2 == '_') || (c2 >= '0' && c2 <= '9') || (c2 >= 'A' && c2 <= 'Z') || (c2 >= 'a' && c2 <= 'z')){
                    if(i == ((size / 2))){
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
                token->value.identifier = str;
                return LEX_OK;
            }
            case '?': { //token can be type or ending sequence
                register int c2 = fgetc(stream);
                if (c2 == '>') { //ending sequence
					c2 = fgetc(stream);
					if(c2 != EOF){
						exit(BAD_SYNTAX);
					}
                    token->type = T_END;
                    token->line = scanner->line;
                    return LEX_OK;
                } else if (c2 >= 'a' && c2 <= 'z') {
                    char *str = malloc(40);
					if(str == NULL){
						exit(BAD_INTERNAL);
					}
                    int size = 40;
                    int i = 0;
                    while (c2 >= 'a' && c2 <= 'z') { //saving the identifier string
													 //(identifiers of types can contain only
													 //lowercase letters)
                        if (i == (size / 2)) {
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
                    if (kw_check(str, token) != 2) { //check for keyword, if the identifier
														//doesn't match any type except void,
														//error occurs
                        token->type = T_ERROR;
                        token->line = scanner->line;
                        free(str);
                        return BAD_LEXEM;
                    }
                    token->line = scanner->line;
					token->strict_type = false; //variable of this type can contain null
                    return LEX_OK;

                } else { //anything else causes an error
                    token->type = T_ERROR;
                    token->line = scanner->line;
                    return BAD_LEXEM;
                }
            }
            case '"': { //token is string
                token->type = T_STRING;
                token->line = scanner->line;
                int c2 = fgetc(stream);
                if(c2 == '"'){ //empty string
                    token->value.string = "";
                    return LEX_OK;
                }
				int size = 40;
                char *str = malloc(size);
				if(str == NULL){
					exit(BAD_INTERNAL);
				}
                int i = 0;
                while (true) { //iterating through file until the ending quotation mark is found
							   //and saving the string
                    if (i == (size / 2)) {
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
					if(c2 == '$'){ //if dollar sign is found and is not escaped, error occurs
						token->type = T_ERROR;
						token->line = scanner->line;
						free(str);
						return BAD_LEXEM;
					}
                    if(c2 == '\\'){
                        c2 = fgetc(stream);
                        str[i] = (char) c2;
                        i++;
                    }
					if(c2 < 32){ //if any directly written character has ordinal value lesser
								 //than 32, error occurs
						token->type = T_ERROR;
						token->line = scanner->line;
						free(str);
						return BAD_LEXEM;
					}
                    c2 = fgetc(stream);
                    if (c2 == '"') { //ending quotation mark found, insert terminating null
									 //and break out of loop
                        str[i] = '\0';
                        break;
                    }else if(c2 == EOF){ //if end of file is found before ending the string,
										 //error occurs
                        token->type = T_ERROR;
                        token->line = scanner->line;
                        free(str);
                        return BAD_LEXEM;
                    }
                }
				//passing the converted string to token
                token->value.string = convert_string_for_ifjcode(str, size);
                return LEX_OK;
            }
            default: { //any unknown character causes an error
                token->type = T_ERROR;
                token->line = scanner->line;
                return BAD_LEXEM;
            }
        }
    }
}

/**
 * @brief function to convert strings from IFJ22 to IFJcode22
 * @param str string to be converted
 * @param size current allocated size for the string in bytes
 * @return returns converted string
 */
char* convert_string_for_ifjcode(register char *str, int size) {
    register int i = 0;
    char hex[3];
    char oct[4];
    while(str[i] != '\0'){
		if(str[i] == '\\' && str[i+1] == 'x'){
			//if the escape is hexadecimal
			hex[0] = str[i+2];
			hex[1] = str[i+3];
			hex[2] = '\0';
			if(convert_esc_to_int(hex, 2) == -1){
				int j = size - 1;
				while (j > i + 1) { //if the format doesn't match any allowed sequence,
									//backslash alone is inserted
					str[j] = str[j - 3];
					j--;
				}
				str[i] = '\\';
				str[i+1] = '0';
				str[i+2] = '9';
				str[i+3] = '2';
				i++;
				continue;
			}
			//conversion of escape sequence to decimal integer
			int result = convert_esc_to_int(hex, 2);
			char esc[4];
			sprintf(esc, "%d", result); //conversion of the decimal integer to string
			if(result > 99) { //inserting the converted escape sequence to string
							  //it needs to keep the 3 digit format
				str[i + 1] = esc[0];
				str[i + 2] = esc[1];
				str[i + 3] = esc[2];
			}else if(result > 9){
				str[i + 3] = esc[1];
				str[i + 2] = esc[0];
				str[i + 1] = '0';
			}else{
				str[i + 3] = esc[0];
				str[i + 2] = '0';
				str[i + 1] = '0';
			}
		}else if(str[i] == '\\' && ((str[i+1] >= '0' && str[i+1] <= '3') && (str[i+2] >= '0' && str[i+2] <= '7') && (str[i+3] >= '0' && str[i+3] <= '7'))){
			//if the octal format is matched
			oct[0] = str[i+1];
			oct[1] = str[i+2];
			oct[2] = str[i+3];
			oct[3] = '\0';
			if(convert_esc_to_int(oct, 3) == -1){
				int j = size - 1;
				while (j > i + 1) { //if the format doesn't match any allowed sequence,
									//backslash alone is inserted
					str[j] = str[j - 3];
					j--;
				}
				str[i] = '\\';
				str[i+1] = '0';
				str[i+2] = '9';
				str[i+3] = '2';
				i++;
				continue;
			}
			//conversion of escape sequence to decimal integer
			int result = convert_esc_to_int(oct, 3);
			char esc[4];
			sprintf(esc, "%d", result); //conversion of the decimal integer to string
			if(result > 99) { //inserting the converted escape sequence to string
							  //it needs to keep the 3 digit format
				str[i + 1] = esc[0];
				str[i + 2] = esc[1];
				str[i + 3] = esc[2];
			}else if(result > 9){
				str[i + 3] = esc[1];
				str[i + 2] = esc[0];
				str[i + 1] = '0';
			}else{
				str[i + 3] = esc[0];
				str[i + 2] = '0';
				str[i + 1] = '0';
			}
		}else if(str[i] ==' '){ //space and # have to be written as esc. sequence for the IFJcode22
			int j = size - 1;
			while (j > i + 2) {
				str[j] = str[j - 3];
				j--;
			}
			str[i] = '\\';
			str[i+1] = '0';
			str[i+2] = '3';
			str[i+3] = '2';
		}else if(str[i] =='#'){
			int j = size - 1;
			while (j > i + 2) {
				str[j] = str[j - 3];
				j--;
			}
			str[i] = '\\';
			str[i+1] = '0';
			str[i+2] = '3';
			str[i+3] = '5';
		}
		else if(str[i] == '\\'){ //conversion of escaped characters to numerical escape sequences
			register int j = size - 1;
			switch (str[i+1]) {
				case 'n':
					while (j > i + 1) { //making space in the string
						str[j] = str[j - 2];
						j--;
					}
					str[i+1] = '0'; //inserting escape sequence
					str[i+2] = '1';
					str[i+3] = '0';
					break;
				case 't':
					while (j > i + 1) {
						str[j] = str[j - 2];
						j--;
					}
					str[i+1] = '0';
					str[i+2] = '0';
					str[i+3] = '9';
					break;
				case 'r':
					while (j > i + 1) {
						str[j] = str[j - 2];
						j--;
					}
					str[i+1] = '0';
					str[i+2] = '1';
					str[i+3] = '3';
					break;
				case 'e':
					while (j > i + 1) {
						str[j] = str[j - 2];
						j--;
					}
					str[i+1] = '0';
					str[i+2] = '2';
					str[i+3] = '7';
					break;
				case 'a':
					while (j > i + 1) {
						str[j] = str[j - 2];
						j--;
					}
					str[i+1] = '0';
					str[i+2] = '0';
					str[i+3] = '7';
					break;
				case 'f':
					while (j > i + 1) {
						str[j] = str[j - 2];
						j--;
					}
					str[i+1] = '0';
					str[i+2] = '1';
					str[i+3] = '2';
					break;
				case 'v':
					while (j > i + 1) {
						str[j] = str[j - 2];
						j--;
					}
					str[i+1] = '0';
					str[i+2] = '1';
					str[i+3] = '1';
					break;
				case '\\':
					while (j > i + 1) {
						str[j] = str[j - 2];
						j--;
					}
					str[i+1] = '0';
					str[i+2] = '9';
					str[i+3] = '2';
					break;
				case '$':
					while (j > i + 1) {
						str[j] = str[j - 2];
						j--;
					}
					str[i+1] = '0';
					str[i+2] = '3';
					str[i+3] = '6';
					break;
				case '"':
					while (j > i + 1) {
						str[j] = str[j - 2];
						j--;
					}
					str[i+1] = '0';
					str[i+2] = '3';
					str[i+3] = '4';
					break;
				case '\'':
					while (j > i + 1) {
						str[j] = str[j - 2];
						j--;
					}
					str[i+1] = '0';
					str[i+2] = '3';
					str[i+3] = '9';
					break;
				default: //if the sequence doesn't match any allowed format then backslash alone is written
					while (j > i + 2) {
						str[j] = str[j - 3];
						j--;
					}
					str[i+1] = '0';
					str[i+2] = '9';
					str[i+3] = '2';
					break;
			}
		}
		i++;
		if (i == (size / 2)) { //expanding allocated space for the string,
			 				   //so it doesn't overflow by adding too many escape sequences
			size *= 2;
			char *tmp = realloc(str, size);
			if(tmp == NULL){
				free(str);
				exit(BAD_INTERNAL);
			}
			str = tmp;
		}
    }
    return str;
}

/**
 * @brief function to convert octal or hexadecimal number from escape sequence to decimal integer
 * @param str escape sequence as string
 * @param len length of escape sequence - 2 for hexadecimal, 3 for octal
 * @return returns the converted integer or -1 if the sequence is out of bounds or $
 */
int convert_esc_to_int(const char* str, int len) {
    int result = 0;
    if (len == 3) {
        result = (int) strtol(str, NULL, 8); //conversion from octal to decimal
        if(result > 255 || result == 36 || result < 1){
            return -1;
        }
    }else if(len == 2) {
        if(str[0] < '0' || (str[0] > '9' && str[0] < 'A') || (str[0] > 'F' && str[0] < 'a') || str[0] > 'f'){
            return -1;
        }
        if(str[1] < '0' || (str[1] > '9' && str[1] < 'A') || (str[1] > 'F' && str[1] < 'a') || str[1] > 'f' ){
            return -1;
        }
        result = (int) strtol(str, NULL, 16); //conversion from hexadecimal to decimal
        if(result == 36 || result < 1){
            return -1;
        }
    }
    return result;
}

/**
 * @brief function to check if the passed string is a keyword
 * @param s string to be checked for keyword
 * @param token current token
 * @return returns 0 if no keyword is found, 2 for types except void, 1 for other keywords
 */
int kw_check(const char * restrict s, Token * restrict token){
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
